#ifndef QPICONFIG_H
#define QPICONFIG_H

#include "QFile"
#include "QVector"
#include "QStringList"
#include "QTextStream"

#include <QColor>
#include <QPointF>
#include <QRectF>
#include <QDebug>
#include <cmath>


inline QByteArray QString2QByteArray(const QString & string) {return qUncompress(QByteArray::fromBase64(string.toLatin1()));}
int QString2int(const QString & string);
inline QColor QString2QColor(const QString & string) {return (string.left(1) == "#" ? QColor(string.right(string.length() - 1).toInt(0, 16)) : QColor(QString2int(string)));}
QRect QString2QRect(const QString & string);
QRectF QString2QRectF(const QString & string);
QPoint QString2QPoint(const QString & string);
QPointF QString2QPointF(const QString & string);

inline QString QColor2QString(const QColor & color) {QString s = color.name(); return "0x" + QString::number(color.alpha(), 16).rightJustified(2, '0') + s.right(s.length() - 1);}
inline QString QPoint2QString(const QPoint & point) {return QString::number(point.x()) + ";" + QString::number(point.y());}
inline QString QPointF2QString(const QPointF & point) {return QString::number(point.x()) + ";" + QString::number(point.y());}
inline QString QByteArray2QString(const QByteArray & array) {return QString(qCompress(array, 9).toBase64());}
QString QRect2QString(const QRect & rect);
QString QRectF2QString(const QRectF & rect);

#define QPICONFIG_GET_VALUE \
		Entry & getValue(const QString & vname, const char * def, bool * exist = 0) {return getValue(vname, QString(def), exist);} \
		Entry & getValue(const QString & vname, const QStringList & def, bool * exist = 0) {return getValue(vname, def.join("%|%"), exist);} \
		Entry & getValue(const QString & vname, const bool def, bool * exist = 0) {return getValue(vname, QString::number(def), exist);} \
		Entry & getValue(const QString & vname, const short def, bool * exist = 0) {return getValue(vname, QString::number(def), exist);} \
		Entry & getValue(const QString & vname, const int def, bool * exist = 0) {return getValue(vname, QString::number(def), exist);} \
		Entry & getValue(const QString & vname, const long def, bool * exist = 0) {return getValue(vname, QString::number(def), exist);} \
		Entry & getValue(const QString & vname, const uchar def, bool * exist = 0) {return getValue(vname, QString::number(def), exist);} \
		Entry & getValue(const QString & vname, const ushort def, bool * exist = 0) {return getValue(vname, QString::number(def), exist);} \
		Entry & getValue(const QString & vname, const uint def, bool * exist = 0) {return getValue(vname, QString::number(def), exist);} \
		Entry & getValue(const QString & vname, const ulong def, bool * exist = 0) {return getValue(vname, QString::number(def), exist);} \
		Entry & getValue(const QString & vname, const float def, bool * exist = 0) {return getValue(vname, QString::number(def), exist);} \
		Entry & getValue(const QString & vname, const double def, bool * exist = 0) {return getValue(vname, QString::number(def), exist);} \
		Entry & getValue(const QString & vname, const QColor & def, bool * exist = 0) {return getValue(vname, QColor2QString(def), exist);} \
		Entry & getValue(const QString & vname, const Qt::GlobalColor def, bool * exist = 0) {return getValue(vname, QColor(def), exist);} \
		Entry & getValue(const QString & vname, const QRect & def, bool * exist = 0) {return getValue(vname, QRect2QString(def), exist);} \
		Entry & getValue(const QString & vname, const QRectF & def, bool * exist = 0) {return getValue(vname, QRectF2QString(def), exist);} \
		Entry & getValue(const QString & vname, const QPoint & def, bool * exist = 0) {return getValue(vname, QPoint2QString(def), exist);} \
		Entry & getValue(const QString & vname, const QPointF & def, bool * exist = 0) {return getValue(vname, QPointF2QString(def), exist);} \
		Entry & getValue(const QString & vname, const QByteArray & def, bool * exist = 0) {return getValue(vname, QByteArray2QString(def), exist);}

class QPIConfig: public QFile
{
	friend class Entry;
	friend class Branch;
	friend class QPIConfigWidget;
public:
	enum FileType {Config, XML};

	QPIConfig(const QString & path, QIODevice::OpenMode mode, QPIConfig::FileType type);
	QPIConfig(const QString & path, QIODevice::OpenMode mode = QIODevice::ReadWrite);
	QPIConfig(const QString & path, QPIConfig::FileType type);
	QPIConfig(QString * str, QPIConfig::FileType type = QPIConfig::Config);
	~QPIConfig();
	
	void setFile(const QString & path, QIODevice::OpenMode mode = QIODevice::ReadWrite);
	void setString(QString * str);

	class Entry;

	class Branch: public QVector<Entry * > {
		friend class QPIConfig;
		friend class Entry;
	public:
		Branch() {;}

		Entry & getValue(const QString & vname, const QString & def = QString(), bool * exist = 0);
		QPICONFIG_GET_VALUE

		Branch allLeaves();
		Branch getValues(const QString & name);
		Branch getLeaves();
		Branch getBranches();
		Branch & filter(const QString & f);
		bool isEntryExists(const QString & name) const {foreach (const Entry * i, *this) if (entryExists(i, name)) return true; return false;}
		int indexOf(const Entry * e) {for (int i = 0; i < size(); ++i) if (at(i) == e) return i; return -1;}

		//void clear() {foreach (Entry * i, *this) delete i; QVector<Entry * >::clear();}

	private:
		bool entryExists(const Entry * e, const QString & name) const;
		void allLeaves(Branch & b, Entry * e) {foreach (Entry * i, e->_children) {if (i->isLeaf()) b << i; else allLeaves(b, i);}}

		static Entry _empty;
		QString delim;

	};

	class Entry {
		friend class QPIConfig;
		friend class Branch;
		friend class QPIConfigWidget;
		friend class ConfigValueWidget;
	public:
        Entry() {_parent = 0; _line = -1;}

		Entry * parent() const {return _parent;}
		int childCount() {return _children.size();}
		Branch & children() {_children.delim = delim; return _children;}
		Entry * child(const int index) const {return _children[index];}
		const Entry * findChild(const QString & name) const {foreach (const Entry * i, _children) if (i->_name == name) return i; return 0;}
		Entry * findChild(const QString & name) {foreach (Entry * i, _children) if (i->_name == name) return i; return 0;}
		bool isLeaf() const {return _children.empty();}

		const QString & name() const {return _name;}
		const QString & value() const {return _value;}
		const QString & type() const {return _type;}
		const QString & comment() const {return _comment;}

		Entry & setName(const QString & value) {_name = value; return *this;}
		Entry & setType(const QString & value) {_type = value; return *this;}
		Entry & setComment(const QString & value) {_comment = value; return *this;}
		Entry & setValue(const QString & value) {_value = value; return *this;}
		Entry & setValue(const QStringList & value) {setValue(value.join("%|%")); setType("l"); return *this;}
		Entry & setValue(const char * value) {setValue(QString(value)); setType("s"); return *this;}
		Entry & setValue(const bool value) {setValue(QString::number(value)); setType("b"); return *this;}
		Entry & setValue(const short value) {setValue(QString::number(value)); setType("n"); return *this;}
		Entry & setValue(const int value) {setValue(QString::number(value)); setType("n"); return *this;}
		Entry & setValue(const long value) {setValue(QString::number(value)); setType("n"); return *this;}
		Entry & setValue(const uchar value) {setValue(QString::number(value)); setType("n"); return *this;}
		Entry & setValue(const ushort value) {setValue(QString::number(value)); setType("n"); return *this;}
		Entry & setValue(const uint value) {setValue(QString::number(value)); setType("n"); return *this;}
		Entry & setValue(const ulong value) {setValue(QString::number(value)); setType("n"); return *this;}
		Entry & setValue(const float value) {setValue(QString::number(value)); setType("f"); return *this;}
		Entry & setValue(const double value) {setValue(QString::number(value)); setType("f"); return *this;}
		Entry & setValue(const QColor & value) {setValue(QColor2QString(value)); setType("c"); return *this;}
		Entry & setValue(const Qt::GlobalColor & value) {setValue(QColor(value)); return *this;}
		Entry & setValue(const QRect & value) {setValue(QRect2QString(value)); setType("r"); return *this;}
		Entry & setValue(const QRectF & value) {setValue(QRectF2QString(value)); setType("a"); return *this;}
		Entry & setValue(const QPoint & value) {setValue(QPoint2QString(value)); setType("p"); return *this;}
		Entry & setValue(const QPointF & value) {setValue(QPointF2QString(value)); setType("v"); return *this;}
		Entry & setValue(const QByteArray & value) {setValue(QByteArray2QString(value)); setType("s"); return *this;}
		
		Entry & getValue(const QString & vname, const QString & def = QString(), bool * exist = 0);
		QPICONFIG_GET_VALUE

		Branch getValues(const QString & vname);

		bool isEntryExists(const QString & name) const {return entryExists(this, name);}
		const QString & stringValue() const {return _value;}

		operator bool() {return (_value.toLower().trimmed() == "true" || _value.toInt() > 0);}
		operator char() {return (_value.isEmpty() ? 0 : _value[0].toLatin1());}
		operator short() {return _value.toShort();}
		operator int() {return QString2int(_value);}
		operator long() {return QString2int(_value);}
		operator uchar() {return QString2int(_value);}
		operator ushort() {return QString2int(_value);}
		operator uint() {return QString2int(_value);}
		operator ulong() {return QString2int(_value);}
		operator float() {return _value.toFloat();}
		operator double() {return _value.toDouble();}
		operator QString() {return _value;}
		operator QStringList() {return _value.split("%|%");}
		operator QColor() {return QString2QColor(_value);}
		operator QRect() {return QString2QRect(_value);}
		operator QRectF() {return QString2QRectF(_value);}
		operator QPoint() {return QString2QPoint(_value);}
		operator QPointF() {return QString2QPointF(_value);}
		operator QByteArray() {return QString2QByteArray(_value);}

	private:
		static bool compare(const QPIConfig::Entry * f, const QPIConfig::Entry * s) {return f->_line < s->_line;}
		bool entryExists(const Entry * e, const QString & name) const;
		void buildLine() {_all = _tab + _full_name + " = " + _value + " #" + _type + " " + _comment;}
		void clear() {_children.clear(); _name = _value = _type = _comment = _all = QString(); _line = 0; _parent = 0;}
		void deleteBranch() {foreach (Entry * i, _children) {i->deleteBranch(); delete i;}}

		static Entry _empty;
		Entry * _parent;
		Branch _children;
		QString _tab;
		QString _name;
		QString _value;
		QString _type;
		QString _comment;
		QString _all;
		QString _full_name;
		QString delim;
		int _line;
	};
	
	Entry & getValue(const QString & vname, const QString & def = QString(), bool * exist = 0);
	QPICONFIG_GET_VALUE

	Branch getValues(const QString & vname);

	void setValue(const QString & name, const QString & value, const QString & type = "s", bool write = true);
	void setValue(const QString & name, const QStringList & value, bool write = true) {setValue(name, value.join("%|%"), "l", write);}
	void setValue(const QString & name, const char * value, bool write = true) {setValue(name, QString(value), "s", write);}
	void setValue(const QString & name, const bool value, bool write = true) {setValue(name, QString::number(value), "b", write);}
	void setValue(const QString & name, const short value, bool write = true) {setValue(name, QString::number(value), "n", write);}
	void setValue(const QString & name, const int value, bool write = true) {setValue(name, QString::number(value), "n", write);}
	void setValue(const QString & name, const long value, bool write = true) {setValue(name, QString::number(value), "n", write);}
	void setValue(const QString & name, const uchar value, bool write = true) {setValue(name, QString::number(value), "n", write);}
	void setValue(const QString & name, const ushort value, bool write = true) {setValue(name, QString::number(value), "n", write);}
	void setValue(const QString & name, const uint value, bool write = true) {setValue(name, QString::number(value), "n", write);}
	void setValue(const QString & name, const ulong value, bool write = true) {setValue(name, QString::number(value), "n", write);}
	void setValue(const QString & name, const float value, bool write = true) {setValue(name, QString::number(value), "f", write);}
	void setValue(const QString & name, const double value, bool write = true) {setValue(name, QString::number(value), "f", write);}
	void setValue(const QString & name, const QColor & value, bool write = true) {setValue(name, QColor2QString(value), "c", write);}
	void setValue(const QString & name, const Qt::GlobalColor & value, bool write = true) {setValue(name, QColor(value), write);}
	void setValue(const QString & name, const QRect & value, bool write = true) {setValue(name, QRect2QString(value), "r", write);}
	void setValue(const QString & name, const QRectF & value, bool write = true) {setValue(name, QRectF2QString(value), "a", write);}
	void setValue(const QString & name, const QPoint & value, bool write = true) {setValue(name, QPoint2QString(value), "p", write);}
	void setValue(const QString & name, const QPointF & value, bool write = true) {setValue(name, QPointF2QString(value), "v", write);}
	void setValue(const QString & name, const QByteArray & value, bool write = true) {setValue(name, QByteArray2QString(value), "s", write);}

	Entry & rootEntry() {return root;}
	int entriesCount() const {return childCount(&root);}
	bool isEntryExists(const QString & name) const {return entryExists(&root, name);}

	Branch allTree() {Branch b; foreach (Entry * i, root._children) b << i; return b;}
    Branch allLeaves() {Branch b; allLeaves(b, &root); std::sort(b.begin(), b.end(), Entry::compare); return b;}
	int entryIndex(const QString & name);

	QString getName(uint number) {return entryByIndex(number)._name;}
	QString getValue(uint number) {return entryByIndex(number)._value;}
	QChar getType(uint number) {return entryByIndex(number)._type[0];}
	QString getComment(uint number) {return entryByIndex(number)._comment;}
	
	QPIConfig::Entry & addEntry(const QString & name, const QString & value, const QString & type = "s", bool write = true, bool node = false);
	void setName(uint number, const QString & name, bool write = true);
	void setValue(uint number, const QString & value, bool write = true);
	void setType(uint number, const QString & type, bool write = true);
	void setComment(uint number, const QString & comment, bool write = true);
	
	void removeEntry(const QString & name, bool write = true);
	void removeEntry(uint number, bool write = true);
	
	void clear();
	void readAll();
	void writeAll();
	QString writeAllToString();
	void readAllFromString(const QString & str);
	
	const QString & delimiter() const {return delim;}
	void setDelimiter(const QString & d) {delim = d; setEntryDelim(&root, d); readAll();}
	
private:
	QPIConfig(const QString & path, QStringList dirs);
	void init();
	int childCount(const Entry * e) const {int c = 0; foreach (const Entry * i, e->_children) c += childCount(i); c += e->_children.size(); return c;}
	bool entryExists(const Entry * e, const QString & name) const;
	void buildFullNames(Entry * e) {foreach (Entry * i, e->_children) {if (e != &root) i->_full_name = e->_full_name + delim + i->_name; else i->_full_name = i->_name; buildFullNames(i);}}
	void allLeaves(Branch & b, Entry * e) {foreach (Entry * i, e->_children) {if ((!i->_value.isEmpty() && !i->isLeaf()) || i->isLeaf()) b << i; allLeaves(b, i);}}
	void setEntryDelim(Entry * e, const QString & d) {foreach (Entry * i, e->_children) setEntryDelim(i, d); e->delim = d;}
	inline Entry & entryByIndex(const int index) {Branch b = allLeaves(); if (index < 0 || index >= b.size()) return empty; return *(b[index]);}
	void removeEntry(Branch & b, Entry * e);
	void deleteEntry(Entry * e) {foreach (Entry * i, e->_children) deleteEntry(i); delete e;}
	QString getPrefixFromLine(QString line, bool * exists);
	void updateIncludes();
	QString parseLine(QString v);
	void parse(QString content = QString());

	int centry;
	bool internal;
	QVector<QPIConfig * > includes, inc_devs;
	Branch all_includes;
	QFile * dev;
	QStringList incdirs;
	QString delim, * buffer;
	Entry root, empty;
	uint lines;
	QStringList other;
	QTextStream stream;
	FileType type;
};

#endif // QPICONFIG_H
