#ifndef MESSAGES_H
#define MESSAGES_H

#include <stdint.h> /*  */
#include <vector>

#include "serial.h"

/// Number of the thrusters
static const uint8_t VmaAmount = 8;

/// Number of the devs
static const uint8_t DevAmount = 6;

void pushToVector(std::vector<char> &vector, int8_t var);
void pushToVector(std::vector<char> &vector, uint8_t var);
void pushToVector(std::vector<char> &vector, int16_t var, bool revert = false);
void pushToVector(std::vector<char> &vector, uint16_t var, bool revert = false);
void pushToVector(std::vector<char> &vector, float var, bool revert = false);

void popFromVector(std::vector<char> &container, int8_t &output);
void popFromVector(std::vector<char> &container, uint8_t &output);
void popFromVector(std::vector<char> &container, int16_t &output, bool revert = true);
void popFromVector(std::vector<char> &container, uint16_t &output, bool revert = true);
void popFromVector(std::vector<char> &container, float &output, bool revert = true);

uint16_t getChecksum16b(std::vector<char> &msg);

/** \brief Structure for storing and processing data from the STM32 normal request message protocol
 * Shore send requests and STM send responses
 */
struct RequestMessage
{
    RequestMessage();

    /// Length in bytes of the normal message protocol
    const static uint8_t length = 26;

    /// Type code for the normal message protocol
    const static uint8_t type = 0xA5;
    uint8_t flags;
    int16_t march;
    int16_t lag;
    int16_t depth;
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    int8_t dev[DevAmount];
    uint8_t dev_flags;
    uint8_t stabilize_flags;
    uint8_t cameras;
    uint8_t pc_reset;
    //uint16_t checksum;

    std::vector<char> formVector();
};

/** \brief Structure for storing and processing data from the STM32 configuration response message protocol
 * Shore send requests and STM send responses
 */
struct ResponseMessage
{
    ResponseMessage();

    /// Length in bytes of the response message protocol
    const static uint8_t length = 70;

    float roll;
    float pitch;
    float yaw;

    float rollSpeed;
    float pitchSpeed;
    float yawSpeed;

    float depth;
    float in_pressure;

    uint8_t dev_state;
    int16_t leak_data;

    uint16_t vma_current[VmaAmount];
    uint16_t dev_current[DevAmount];

    uint16_t vma_errors;
    uint16_t dev_errors;
    uint8_t pc_errors;

    uint16_t checksum;

    bool parseVector(std::vector<char> &input);
};

#endif // MESSAGES_H
