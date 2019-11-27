#include "messages.h"

/** \brief Constructor for RequestMessage
  *
  */
RequestMessage::RequestMessage()
{
    flags = 0;
    march = 0;
    lag = 0;
    depth = 0;
    roll = 0;
    pitch = 0;
    yaw = 0;

    for(int i=0; i<DevAmount; i++) {
        dev[i] = 0;
    }

    dev_flags = 0;
    stabilize_flags = 0;
    cameras = 0;
    pc_reset = 0;
}

/** \brief Form bitwise correct string with computed 16bit checksum from the data stored in RequestMessage
  *
  */
std::vector<char> RequestMessage::formVector()
{
    std::vector<char> container;

    pushToVector(container, type);
    pushToVector(container, flags);

    pushToVector(container, march);
    pushToVector(container, lag);
    pushToVector(container, depth);
    pushToVector(container, roll);
    pushToVector(container, pitch);
    pushToVector(container, yaw);

    for(int i=0; i<DevAmount; i++) {
        pushToVector(container, dev[i]);
    }

    pushToVector(container, dev_flags);
    pushToVector(container, stabilize_flags);
    pushToVector(container, cameras);
    pushToVector(container, pc_reset);

    uint16_t checksum = getChecksum16b(container);
    pushToVector(container, checksum); // do i need to revert bytes here?

    return container;
}

/** \brief Constructor for ResponseMessage
  *
  */
ResponseMessage::ResponseMessage()
{
    roll = 0;
    pitch = 0;
    yaw = 0;

    rollSpeed = 0;
    pitchSpeed = 0;
    yawSpeed = 0;

    depth = 0;
    in_pressure = 0;

    dev_state = 0;
    leak_data = 0;

    for(int i=0; i<VmaAmount; i++) {
        vma_current[i] = 0;
    }

    for(int i=0; i<DevAmount; i++) {
        dev_current[i] = 0;
    }

    vma_errors = 0;
    dev_errors = 0;
    pc_errors = 0;

    checksum = 0;
}

/** \brief Parse string bitwise correctly into ResponseMessage and check 16bit checksum.
  *
  * \param[in]  &input String to parse.
  */
bool ResponseMessage::parseVector(std::vector<char> &input)
{
    popFromVector(input, checksum, true);

    uint16_t checksum_calc = getChecksum16b(input);

    if(checksum_calc != checksum) {
         return false;
     }

    popFromVector(input, pc_errors);
    popFromVector(input, dev_errors);
    popFromVector(input, vma_errors);

    for(int i=0; i<DevAmount; i++) {
        popFromVector(input, dev_current[DevAmount-i]);
    }

    for(int i=0; i<VmaAmount; i++) {
        popFromVector(input, vma_current[VmaAmount-i]);
    }

    popFromVector(input, leak_data);
    popFromVector(input, dev_state);

    popFromVector(input, in_pressure);
    popFromVector(input, depth);

    popFromVector(input, yawSpeed);
    popFromVector(input, pitchSpeed);
    popFromVector(input, rollSpeed);

    popFromVector(input, yaw);
    popFromVector(input, pitch);
    popFromVector(input, roll);

    return true;
}

/** \brief Overloaded transform to string function, transforms value to string bitwise correctly
  *
  * \param[in]  var     Variable to transform.
  * \param[in]  revert  Revert bytes or not.
  */
void pushToVector(std::vector<char> &vector, int8_t var)
{
    char buf = *reinterpret_cast<char*>(&var);
    vector.push_back(buf);
}

/** \brief Overloaded transform to string function, transforms value to string bitwise correctly
  *
  * \param[in]  var     Variable to transform.
  * \param[in]  revert  Revert bytes or not.
  */
void pushToVector(std::vector<char> &vector, uint8_t var)
{
    char buf = *reinterpret_cast<char*>(&var);
    vector.push_back(buf);
}

/** \brief Overloaded transform to string function, transforms value to string bitwise correctly
  *
  * \param[in]  var     Variable to transform.
  * \param[in]  revert  Revert bytes or not.
  */
void pushToVector(std::vector<char> &vector, int16_t var, bool revert)
{
    char *ptr = reinterpret_cast<char*>(&var);
    if(revert) {
        vector.push_back(ptr[1]);
        vector.push_back(ptr[0]);
    }
    else {
        vector.push_back(ptr[0]);
        vector.push_back(ptr[1]);
    }
}

/** \brief Overloaded transform to string function, transforms value to string bitwise correctly
  *
  * \param[in]  var     Variable to transform.
  * \param[in]  revert  Revert bytes or not.
  */
void pushToVector(std::vector<char> &vector, uint16_t var, bool revert)
{
    char *ptr = reinterpret_cast<char*>(&var);
    if(revert) {
        vector.push_back(ptr[1]);
        vector.push_back(ptr[0]);
    }
    else {
        vector.push_back(ptr[0]);
        vector.push_back(ptr[1]);
    }
}

/** \brief Overloaded transform to string function, transforms value to string bitwise correctly
  *
  * \param[in]  var     Variable to transform.
  * \param[in]  revert  Revert bytes or not.
  */
void pushToVector(std::vector<char> &vector, float var, bool revert)
{
    char *ptr = reinterpret_cast<char*>(&var);
    for(int i=0; i<4; i++) {
        if(revert) {
            vector.push_back(ptr[3-i]);
        }
        else {
            vector.push_back(ptr[i]);
        }
    }
}

/** \brief Overloaded pick from string, picks value from the end of the string bitwise correctly
  *
  * \param[out] &container  Link to container string with bytes.
  * \param[out] &value      Link to variable in which the data will be stored.
  * \param[in]  revert      Revert bytes or not.
  */
void popFromVector(std::vector<char> &vector, uint8_t &output)
{
    char *ptr = reinterpret_cast<char*>(&output);
    *ptr = vector.back();
    vector.pop_back();
}

/** \brief Overloaded pick from string, picks value from the end of the string bitwise correctly
  *
  * \param[out] &container  Link to container string with bytes.
  * \param[out] &value      Link to variable in which the data will be stored.
  * \param[in]  revert      Revert bytes or not.
  */
void popFromVector(std::vector<char> &vector, int8_t &output)
{
    char out_raw = vector.back();
    vector.pop_back();
    output = *reinterpret_cast<int8_t*>(&out_raw);
}

/** \brief Overloaded pick from string, picks value from the end of the string bitwise correctly
  *
  * \param[out] &container  Link to container string with bytes.
  * \param[out] &value      Link to variable in which the data will be stored.
  * \param[in]  revert      Revert bytes or not.
  */
void popFromVector(std::vector<char> &vector, int16_t &output, bool revert)
{
    char *ptr = reinterpret_cast<char*>(&output);
    if(revert) {
        ptr[1] = vector.back();
        vector.pop_back();
        ptr[0] = vector.back();
    }
    else {
        ptr[0] = vector.back();
        vector.pop_back();
        ptr[1] = vector.back();
    }
    vector.pop_back();
}

/** \brief Overloaded pick from string, picks value from the end of the string bitwise correctly
  *
  * \param[out] &container  Link to container string with bytes.
  * \param[out] &value      Link to variable in which the data will be stored.
  * \param[in]  revert      Revert bytes or not.
  */
void popFromVector(std::vector<char> &vector, uint16_t &output, bool revert)
{
    char *ptr = reinterpret_cast<char*>(&output);
    if(revert) {
        ptr[1] = vector.back();
        vector.pop_back();
        ptr[0] = vector.back();
    }
    else {
        ptr[0] = vector.back();
        vector.pop_back();
        ptr[1] = vector.back();
    }
    vector.pop_back();
}

/** \brief Overloaded pick from string, picks value from the end of the string bitwise correctly
  *
  * \param[out] &container  Link to container string with bytes.
  * \param[out] &value      Link to variable in which the data will be stored.
  * \param[in]  revert      Revert bytes or not.
  */
void popFromVector(std::vector<char> &vector, float &output, bool revert)
{
    char *ptr = reinterpret_cast<char*>(&output);
    for(size_t i=0; i<4; i++) {
        if(revert) {
            ptr[3-i] = vector.back();
            vector.pop_back();
        }
        else {
            ptr[i] = vector.back();
            vector.pop_back();
        }
    }
}

/** \brief Gets 16 bit checksum for the content of the stream
  *
  * \param[in]  &msg    Link to the stream
  * \param[in]  length  Length of the message in the stream
  */
uint16_t getChecksum16b(std::vector<char> &vector)
{
    size_t len = vector.size();
    uint16_t crc = 0xFFFF;
    uint8_t i = 0;
    uint8_t g = 0;

    while (len--) {
        crc ^= vector[g++] << 8;

        for (i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}

