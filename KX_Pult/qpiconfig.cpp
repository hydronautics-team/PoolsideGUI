#include "qpiconfig.h"
#include <QFileInfo>
#include <QDir>


int QString2int(const QString & string) {
	QString s = string.trimmed();
	if (s.left(2) == "0x") return s.mid(2).toLongLong(0, 16);
	if (s.left(1) == "0") return s.mid(1).toLongLong(0, 8);
	return s.toLongLong();
}


QRect QString2QRect(const QString & string) {
	int sl, st, sw, sh;
	int s = 0, e;
	e = string.indexOf(";");
	sl = string.mid(s, e - s).toInt();
	s = e + 1;
	e = string.indexOf(";", s);
	st = string.mid(s, e - s).toInt();
	s = e + 1;
	e = string.indexOf(";", s);
	sw = string.mid(s, e - s).toInt();
	s = e + 1;
	e = string.length();
	sh = string.mid(s, e - s).toInt();
	return QRect(sl, st, sw, sh);
}


QRectF QString2QRectF(const QString & string) {
	double sl, st, sw, sh;
	int s = 0, e;
	e = string.indexOf(";");
	sl = string.mid(s, e - s).toDouble();
	s = e + 1;
	e = string.indexOf(";", s);
	st = string.mid(s, e - s).toDouble();
	s = e + 1;
	e = string.indexOf(";", s);
	sw = string.mid(s, e - s).toDouble();
	s = e + 1;
	e = string.length();
	sh = string.mid(s, e - s).toDouble();
	return QRectF(sl, st, sw, sh);
}


QPoint QString2QPoint(const QString & string) {
	int sx, sy;
	int s = 0, e;
	e = string.indexOf(";");
	sx = string.mid(s, e - s).toInt();
	s = e + 1;
	e = string.length();
	sy = string.mid(s, e - s).toInt();
	return QPoint(sx, sy);
}


QPointF QString2QPointF(const QString & string) {
	double sx, sy;
	int s = 0, e;
	e = string.indexOf(";");
	sx = string.mid(s, e - s).toDouble();
	s = e + 1;
	e = string.length();
	sy = string.mid(s, e - s).toDouble();
	return QPointF(sx, sy);
}


QString QRect2QString(const QRect & rect) {
	return QString::number(rect.left()) + ";" +
		   QString::number(rect.top()) + ";" +
		   QString::number(rect.width()) + ";" +
		   QString::number(rect.height());
}


QString QRectF2QString(const QRectF & rect) {
	return QString::number(rect.left()) + ";" +
		   QString::number(rect.top()) + ";" +
		   QString::number(rect.width()) + ";" +
		   QString::number(rect.height());
}


QPIConfig::Entry QPIConfig::Branch::_empty;
QPIConfig::Entry QPIConfig::Entry::_empty;


QPIConfig::Branch QPIConfig::Branch::allLeaves() {
	Branch b;
	b.delim = delim;
	foreach (Entry * i, *this) {
		if (i->isLeaf()) b << i;
		else allLeaves(b, i);
	}
	return b;
}


QPIConfig::Entry & QPIConfig::Branch::getValue(const QString & vname, const QString & def, bool * exist) {
	if (vname.isEmpty()) {
		_empty.clear();
		_empty.delim = delim;
		if (exist != 0) *exist = false;
		return _empty;
	}
	QStringList tree = vname.split(delim);
	QString name = tree.front();
	tree.pop_front();
	Entry * ce = 0;
	foreach (Entry * i, *this)
		if (i->_name == name) {
			ce = i;
			break;
		}
	if (ce == 0) {
		_empty._name = vname;
		_empty._value = def;
		_empty.delim = delim;
		if (exist != 0) *exist = false;
		return _empty;
	}
	foreach (QString i, tree) {
		ce = ce->findChild(i);
		if (ce == 0) {
			_empty._name = vname;
			_empty._value = def;
			_empty.delim = delim;
			if (exist != 0) *exist = false;
			return _empty;
		}
	}
	if (exist != 0) *exist = true;
	return *ce;
}


QPIConfig::Branch QPIConfig::Branch::getValues(const QString & name) {
	Branch b;
	b.delim = delim;
	foreach (Entry * i, *this) {
		if (i->isLeaf()) {
			if (i->_name.indexOf(name) >= 0)
				b << i;
		} else {
			foreach (Entry * j, i->_children)
				if (j->_name.indexOf(name) >= 0)
					b << j;
		}
	}
	return b;
}


QPIConfig::Branch QPIConfig::Branch::getLeaves() {
	Branch b;
	b.delim = delim;
	foreach (Entry * i, *this)
		if (i->isLeaf())
			b << i;
	return b;
}


QPIConfig::Branch QPIConfig::Branch::getBranches() {
	Branch b;
	b.delim = delim;
	foreach (Entry * i, *this)
		if (!i->isLeaf())
			b << i;
	return b;
}


QPIConfig::Branch & QPIConfig::Branch::filter(const QString & f) {
	for (int i = 0; i < size(); ++i) {
		if (at(i)->_name.indexOf(f) < 0) {
			remove(i);
			--i;
		}
	}
	return *this;
}


bool QPIConfig::Branch::entryExists(const Entry * e, const QString & name) const {
	if (e->_children.isEmpty()) {
		if  (e->_name == name) return true;
		else return false;
	}
	foreach (Entry * i, e->_children)
		if (entryExists(i, name)) return true;
	return false;
}


QPIConfig::Entry & QPIConfig::Entry::getValue(const QString & vname, const QString & def, bool * exist) {
	QStringList tree = vname.split(delim);
	Entry * ce = this;
	foreach (QString i, tree) {
		ce = ce->findChild(i);
		if (ce == 0) {
			_empty._name = vname;
			_empty._value = def;
			_empty.delim = delim;
			if (exist != 0) *exist = false;
			return _empty;
		}
	}
	if (exist != 0) *exist = true;
	return *ce;
}


QPIConfig::Branch QPIConfig::Entry::getValues(const QString & vname) {
	Branch b;
	b.delim = delim;
	foreach (Entry * i, _children)
		if (i->_name.indexOf(vname) >= 0)
			b << i;
	return b;
};


bool QPIConfig::Entry::entryExists(const Entry * e, const QString & name) const {
	if (e->_children.isEmpty()) {
		if  (e->_name == name) return true;
		else return false;
	}
	foreach (Entry * i, e->_children)
		if (entryExists(i, name)) return true;
	return false;
}


QPIConfig::QPIConfig(const QString & path, QIODevice::OpenMode mode, QPIConfig::FileType type_): QFile(path) {
	init();
	type = type_;
	open(mode);
	//stream.setDevice(this);
	parse();
}


QPIConfig::QPIConfig(const QString & path, QIODevice::OpenMode mode): QFile(path) {
	init();
	type = Config;
	open(mode);
	//stream.setDevice(this);
	parse();
}


QPIConfig::QPIConfig(const QString & path, QPIConfig::FileType type_): QFile(path) {
	init();
	type = type_;
	open(QIODevice::ReadWrite);
	//stream.setDevice(this);
	parse();
}


QPIConfig::QPIConfig(QString * str, QPIConfig::FileType type_) {
	init();
	type = type_;
	buffer = str;
	//stream.setDevice(this);
	parse();
}


QPIConfig::QPIConfig(const QString & path, QStringList dirs) {
	init();
	type = Config;
	internal = true;
	dev = new QFile(path);
	dev->open(QIODevice::ReadOnly);
	incdirs = dirs;
	incdirs << QFileInfo(path).absoluteDir().path();
	QString cp = path;
	while (!dev->isOpen()) {
		if (dirs.isEmpty()) break;
		cp = dirs.back();
		if (cp.endsWith("/") || cp.endsWith("\\")) cp.chop(1);
		cp += "/" + path;
		dev->setFileName(cp);
		dev->open(QIODevice::ReadOnly);
		dirs.pop_back();
	}
	if (!dev->isOpen()) {
		delete dev;
		dev = 0;
		return;
	}
	dev->close();
	setFileName(cp);
	open(QIODevice::ReadOnly);
	parse();
}


QPIConfig::~QPIConfig() {
	stream.setDevice(0);
	root.deleteBranch();
	foreach (QPIConfig * c, inc_devs)
		delete c;
	inc_devs.clear();
	includes.clear();
}


void QPIConfig::init() {
	internal = false;
	buffer = 0;
	dev = 0;
	delim = ".";
	root._name = "root";
	root.delim = delim;
	empty.delim = delim;
	empty._parent = 0;
}


void QPIConfig::setFile(const QString & path, QIODevice::OpenMode mode) {
	buffer = 0;
	setFileName(path);
	if (open(mode))
		parse();
}


void QPIConfig::setString(QString * str) {
	buffer = str;
	parse();
}


QPIConfig::Entry & QPIConfig::getValue(const QString & vname, const QString & def, bool * exist) {
	QStringList tree = vname.split(delim);
	Entry * ce = &root;
	foreach (QString i, tree) {
		ce = ce->findChild(i);
		if (ce == 0) {
			if (exist != 0) *exist = false;
			empty._name = vname;
			empty._value = def;
			empty.delim = delim;
			return empty;
		}
	}
	if (exist != 0) *exist = true;
	return *ce;
}


QPIConfig::Branch QPIConfig::getValues(const QString & vname) {
	Branch b;
	b.delim = delim;
	foreach (Entry * i, root._children)
		if (i->_name.indexOf(vname) >= 0)
			b << i;
	return b;
}


QPIConfig::Entry & QPIConfig::addEntry(const QString & name, const QString & value, const QString & type, bool write, bool node) {
	if (getValue(name)._parent != 0)
		return empty;
	QString sn = name, tn;
	bool toRoot = false;
	while (sn.indexOf(delim) == 0) sn.remove(0, delim.length());
	QStringList tree = sn.split(delim);
	QString ename = tree.back();
	tn = tree.front();
	tree.pop_back();
	Entry * te, * ce, * entry = &root;
	if (tree.isEmpty()) toRoot = true;
	foreach (QString i, tree) {
		te = entry->findChild(i);
		if (te == 0) {
			ce = new Entry();
			ce->delim = delim;
			ce->_tab = entry->_tab;
			ce->_line = entry->_line;
			ce->_name = i;
			ce->_parent = entry;
			//qDebug() << " [QPIC] add " + tn;
			ce->_full_name = tn;
			entry->_children << ce;
			entry = ce;
		} else entry = te;
		tn += delim + i;
	}
	QPIConfig::Branch ch = entry->_children;
    std::sort(ch.begin(), ch.end(), QPIConfig::Entry::compare);
	te = (entry->isLeaf() ? 0 : ch.back());
	ce = new Entry();
	ce->delim = delim;
	ce->_name = ename;
	if (!node) ce->_value = value;
	ce->_type = type;
	if (te == 0) {
		//qDebug() << "[QPIC] te == 0";
		ce->_tab = entry->_tab;
		if (toRoot) ce->_line = other.size();
		else {
			ch = entry->_parent->_children;
            std::sort(ch.begin(), ch.end(), QPIConfig::Entry::compare);
			ce->_line = ch.back()->_line + 1;
		}
	} else {
		ce->_tab = te->_tab;
		if (toRoot) ce->_line = other.size();
		else ce->_line = te->_line + 1;
	}
	//qDebug() << "[QPIC] add " + sn + " at line " << ce->_line << ", parent " << entry->_name;
	ce->_full_name = sn;
	ce->_parent = entry;
	entry->_children << ce;
	//qDebug() << "[QPIC] children " << entry->childCount();
	if (!node) {
		other.insert(ce->_line, "");
		Branch b = allLeaves();
		//qDebug() << "[QPIC] allLeaves " << b.size();
		bool found = false;
		for (int i = 0; i < b.size(); ++i) {
			if (found) {
				b[i]->_line++;
				continue;
			}
			if (b[i] == ce) {
				found = true;
				if (i > 0)
					if (b[i - 1]->_line == b[i]->_line)
						b[i - 1]->_line++;
			}
			//qDebug() << b[i]->_line;
		}
	}
	//qDebug() << "[QPIC] add " + sn + " at line " << ce->_line << ", parent " + entry->_name;
	if (write) writeAll();
	return *ce;
}


void QPIConfig::setValue(const QString & name, const QString & value, const QString & type, bool write) {
	Entry & e(getValue(name));
	if (&e == &empty) {
		addEntry(name, value, type, write);
		return;
	}
	e._value = value;
	e._type = type;
	if (write) writeAll();
}


int QPIConfig::entryIndex(const QString & name) {
	QStringList tree = name.split(delim);
	Entry * ce = &root;
	foreach (QString i, tree) {
		ce = ce->findChild(i);
		if (ce == 0)
			return -1;
	}
	Branch b = allLeaves();
	return allLeaves().indexOf(ce);
}


void QPIConfig::setValue(uint number, const QString & value, bool write) {
	Entry & e(entryByIndex(number));
	if (&e == &empty) return;
	e._value = value;
	if (write) writeAll();
}


void QPIConfig::setName(uint number, const QString & name, bool write) {
	Entry & e(entryByIndex(number));
	if (&e == &empty) return;
	e._name = name;
	if (write) writeAll();
}


void QPIConfig::setType(uint number, const QString & type, bool write) {
	Entry & e(entryByIndex(number));
	if (&e == &empty) return;
	e._type = type;
	if (write) writeAll();
}


void QPIConfig::setComment(uint number, const QString & comment, bool write) {
	Entry & e(entryByIndex(number));
	if (&e == &empty) return;
	e._comment = comment;
	if (write) writeAll();
}


void QPIConfig::removeEntry(const QString & name, bool write) {
	Entry & e(getValue(name));
	if (&e == &empty) return;
	Branch b = allLeaves();
	removeEntry(b, &e);
	if (write) writeAll();
}


void QPIConfig::removeEntry(uint number, bool write) {
	Entry & e(entryByIndex(number));
	if (&e == &empty) return;
	Branch b = allLeaves();
	removeEntry(b, &e);
	if (write) writeAll();
}


void QPIConfig::removeEntry(Branch & b, QPIConfig::Entry * e) {
	bool leaf = true;
	//qDebug() << " before " << b.size();
	if (e->isLeaf()) other.removeAt(e->_line);
	if (!e->isLeaf() && !e->_value.isEmpty()) {
		e->_value.clear();
		//leaf = false;
	} else {
		int cc = e->_children.size();
		for (int i = 0; i < cc; ++i)
			removeEntry(b, e->_children.back());
	}
	bool found = false;
	for (int i = 0; i < b.size(); ++i) {
		if (found) {
			b[i]->_line--;
			continue;
		}
		if (b[i] == e) found = true;
	}
	if (!leaf) return;
	int ti = e->_parent->_children.indexOf(e);
	if (ti >= 0) e->_parent->_children.remove(ti);
	ti = b.indexOf(e);
	if (ti >= 0) b.remove(ti);
	//qDebug() << " after " << b.size();
	delete e;
}


void QPIConfig::writeAll() {
	if (buffer == 0) {
		stream.setDevice(this);
		resize(0);
	} else {
		stream.setString(buffer);
		buffer->clear();
	}
	stream.seek(0);
	//writeEntry(&root);
	buildFullNames(&root);
	Branch b = allLeaves();
	QString prefix, tprefix;
	bool isPrefix;
	int j = 0;
	for (int i = 0; i < other.size(); ++i) {
		//cout << j << endl;
		if (j >= 0 && j < b.size()) {
			if (b[j]->_line == i) {
				b[j]->buildLine();
				stream << b[j]->_all << '\n';
				++j;
			} else {
				stream << other[i];
				tprefix = getPrefixFromLine(other[i], &isPrefix);
				if (isPrefix) {
					prefix = tprefix;
					if (!prefix.isEmpty())
						prefix += delim;
				}
				if (i < other.size() - 1) stream << '\n';
			}
		} else {
			stream << other[i];
			tprefix = getPrefixFromLine(other[i], &isPrefix);
			if (isPrefix) {
				prefix = tprefix;
				if (!prefix.isEmpty())
					prefix += delim;
			}
			if (i < other.size() - 1) stream << '\n';
		}
	}
	if (buffer == 0)
		flush();
	readAll();
}


QString QPIConfig::getPrefixFromLine(QString line, bool * exists) {
	line = line.trimmed();
	if (line.left(1) == "#") {if (exists) *exists = false; return QString();}
	int ci = line.indexOf("#");
	if (ci >= 0) line = line.left(ci).trimmed();
	if (line.indexOf("=") >= 0) {if (exists) *exists = false; return QString();}
	if (line.indexOf("[") >= 0 && line.indexOf("]") >= 0) {
		if (exists) *exists = true;
		line.remove(0, 1);
		return line.left(line.lastIndexOf("]")).trimmed();
	}
	if (exists) *exists = false;
	return QString();
}


QString QPIConfig::writeAllToString() {
	QString str;
	QTextStream s(&str);
	//writeEntry(&root);
	buildFullNames(&root);
	Branch b = allLeaves();
	int j = 0;
	for (int i = 0; i < other.size(); ++i) {
		//cout << j << endl;
		if (j >= 0 && j < b.size()) {
			if (b[j]->_line == i) {
				b[j]->buildLine();
				s << b[j]->_all << '\n';
				++j;
			} else {
				s << other[i];
				if (i < other.size() - 1) s << '\n';
			}
		} else {
			s << other[i];
			if (i < other.size() - 1) s << '\n';
		}
	}
	return str;
}


void QPIConfig::readAllFromString(const QString & str) {
	parse(str);
}


void QPIConfig::clear() {
	root.deleteBranch();
	root.clear();
	other.clear();
	if (buffer == 0)
		resize(0);
	else
		buffer->clear();
	stream.seek(0);
}


void QPIConfig::readAll() {
	if (buffer == 0)
		flush();
	parse();
}


bool QPIConfig::entryExists(const Entry * e, const QString & name) const {
	if (e->_children.isEmpty()) {
		if  (e->_name == name) return true;
		else return false;
	}
	foreach (Entry * i, e->_children)
		if (entryExists(i, name)) return true;
	return false;
}


void QPIConfig::updateIncludes() {
	if (internal) return;
	all_includes.clear();
	foreach (QPIConfig * c, includes)
		all_includes << c->allLeaves();
}


QString QPIConfig::parseLine(QString v) {
	int i = -1, l = 0;
	while (1) {
		i = v.indexOf("${");
		if (i < 0) break;
		l = v.indexOf("}", i + 1);
		QString w = v.mid(i + 2, l - i - 2), r;
		l = w.length() + 3;
		w = parseLine(w);
		w = w.trimmed();
		bool ex = false;
		QPIConfig::Entry & me = getValue(w, "", &ex);
		if (ex) {
			r = me._value;
		} else {
			foreach (QPIConfig::Entry * e, all_includes) {
				if (e->_full_name == w) {
					r = e->_value;
					break;
				}
			}
		}
		v.replace(i, l, r);
	}
	return v;
}


void QPIConfig::parse(QString content) {
	root.deleteBranch();
	root.clear();
	QString src, str, tab, comm, all, name, type, prefix, tprefix;
	QStringList tree;
	Entry * entry, * te, * ce;
	int ind, sind;
	bool isNew, isPrefix;
	foreach (QPIConfig * c, inc_devs)
		delete c;
	inc_devs.clear();
	includes.clear();
	if (content.isEmpty()) {
		if (buffer == 0) {
			if (!isOpen()) return;
			stream.setDevice(this);
		} else
			stream.setString(buffer);
	} else {
		stream.setString(&content);
	}
	stream.seek(0);
	other.clear();
	lines = centry = 0;
	while (!stream.atEnd()) {
		other.push_back(QString());
		src = str = parseLine(stream.readLine());
		tprefix = getPrefixFromLine(src, &isPrefix);
		if (isPrefix) {
			prefix = tprefix;
			if (!prefix.isEmpty())
				prefix += delim;
		}
		//cout << str << endl;
		tab = str.left(str.indexOf(str.trimmed().left(1)));
		str = str.trimmed();
		all = str;
		ind = str.indexOf('=');
		if ((ind > 0) && !(str[0] == '#')) {
			sind = str.indexOf('#');
			if (sind > 0) {
				comm = str.right(str.length() - sind - 1).trimmed();
				if (comm.length() > 0) type = comm[0];
				else type = "s";
				comm = comm.right(comm.length() - 1).trimmed();
				str = str.left(sind);
			} else {
				type = "s";
				comm = "";
			}
			//name = str.left(ind).trimmed();
			tree = (prefix + str.left(ind).trimmed()).split(delim);
			if (tree.front() == "include") {
				name = str.right(str.length() - ind - 1).trimmed();
				QPIConfig * iconf = new QPIConfig(name, incdirs);
				if (!iconf->dev) {
					delete iconf;
				} else {
					inc_devs << iconf;
					includes << iconf << iconf->includes;
					updateIncludes();
				}
				//piCout << "includes" << includes;
				other.back() = src;
			} else {
				name = tree.back();
				tree.pop_back();
				entry = &root;
				foreach (QString i, tree) {
					te = entry->findChild(i);
					if (te == 0) {
						ce = new Entry();
						ce->delim = delim;
						ce->_tab = tab;
						ce->_line = lines;
						ce->_name = i;
						ce->_parent = entry;
						entry->_children << ce;
						entry = ce;
					} else entry = te;
				}
				isNew = false;
				ce = entry->findChild(name);
				if (ce == 0) {
					ce = new Entry();
					isNew = true;
				}
				ce->delim = delim;
				ce->_tab = tab;
				ce->_name = name;
				ce->_value = str.right(str.length() - ind - 1).trimmed();
				ce->_type = type;
				ce->_comment = comm;
				ce->_line = lines;
				ce->_all = all;
				if (isNew) {
					ce->_parent = entry;
					entry->_children << ce;
				}
			}
		} else other.back() = src;
		lines++;
	}
	setEntryDelim(&root, delim);
	buildFullNames(&root);
	//if (content.isEmpty()) stream.setDevice(this);
}
