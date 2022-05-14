#ifndef _EEPROMSTORE_H
#define _EEPROMSTORE_H

#define EEPROM_START_ADDRESS 0
#define CFG_VERSION 0xA1

#include <avr/eeprom.h>
#include <util/crc16.h>

template <class TData>
class EEPROMStore {
    // The data stored in the eprom. The EEMEM complier attribute instructs
    // the complier to locate this variable in the eeprom.
    struct CEEPROMData {
        uint8_t m_cfgVersion;
        uint16_t m_uChecksum;
        TData m_UserData;
    };

public:
    TData Data;

    EEPROMStore()
    {
        Reset();
        if (!Load())
            Reset();
    }

    bool Load()
    {
        CEEPROMData WorkingCopy;
        if (Load(WorkingCopy)) {
            memcpy(&Data, &WorkingCopy.m_UserData, sizeof(TData));
            return true;
        }

        return false;
    }

    bool Save()
    {
        // We only save if the current version in the eeprom doesn't match the data we plan to save.
        // This helps protect the eeprom against save called many times within the arduino loop,
        // though it makes things a little slower.
        uint16_t uChecksum = CalculateChecksum(Data);
        CEEPROMData StoredVersion;
        if (!Load(StoredVersion) || StoredVersion.m_uChecksum != uChecksum || memcmp(&StoredVersion.m_UserData, &Data, sizeof(Data)) != 0) {
            uint16_t addr = EEPROM_START_ADDRESS;
            eeprom_update_byte((uint8_t*)addr, CFG_VERSION);

            // Write checksum
            addr += sizeof(CEEPROMData::m_cfgVersion);
            eeprom_update_word((uint16_t*)addr, uChecksum);

            // Write data
            addr += sizeof(CEEPROMData::m_uChecksum);
            eeprom_update_block(&Data, (void*)addr, sizeof(Data));
            return true;
        }
        return false;
    }

    void Reset()
    {
        Data.Reset();
    }

private:
    // Returns true if checksum in eeprom equals calculated checksum for userdata and version in eeprom equals CFG_VERSION
    bool Load(CEEPROMData& Result)
    {
        eeprom_read_block(&Result, (const void*)EEPROM_START_ADDRESS, sizeof(CEEPROMData));
        uint16_t uChecksum = CalculateChecksum(Result.m_UserData);
        return uChecksum == Result.m_uChecksum && Result.m_cfgVersion == CFG_VERSION;
    }

    uint16_t CalculateChecksum(const TData& TestData) const
    {
        uint16_t uChecksum = 0;
        const uint8_t* pRawData = reinterpret_cast<const uint8_t*>(&TestData);
        size_t szData = sizeof(TestData);

        while (szData--) {
            uChecksum = _crc16_update(uChecksum, *pRawData++);
        }

        return uChecksum;
    }
};

#endif