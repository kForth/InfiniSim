#pragma once
#include <cstddef>
#include <cstdint>
#include <fstream>

namespace Pinetime {
namespace Drivers {
namespace Infinisim {
class SpiNorFlash {
public:
  explicit SpiNorFlash(const std::string &memoryFilePath);
  ~SpiNorFlash();
  SpiNorFlash(const SpiNorFlash &) = delete;
  SpiNorFlash &operator=(const SpiNorFlash &) = delete;
  SpiNorFlash(SpiNorFlash &&) = delete;
  SpiNorFlash &operator=(SpiNorFlash &&) = delete;

  struct __attribute__((packed)) Identification {
    uint8_t manufacturer = 0;
    uint8_t type = 0;
    uint8_t density = 0;
  };

  Identification ReadIdentification();
  uint8_t ReadStatusRegister();
  bool WriteInProgress();
  bool WriteEnabled();
  uint8_t ReadConfigurationRegister();
  void Read(uint32_t address, uint8_t *buffer, size_t size);
  void Write(uint32_t address, const uint8_t *buffer, size_t size);
  void WriteEnable();
  void SectorErase(uint32_t sectorAddress);
  uint8_t ReadSecurityRegister();
  bool ProgramFailed();
  bool EraseFailed();

  void Init();
  void Uninit();

  void Sleep();
  void Wakeup();

private:
  enum class Commands : uint8_t {
    PageProgram = 0x02,
    Read = 0x03,
    ReadStatusRegister = 0x05,
    WriteEnable = 0x06,
    ReadConfigurationRegister = 0x15,
    SectorErase = 0x20,
    ReadSecurityRegister = 0x2B,
    ReadIdentification = 0x9F,
    ReleaseFromDeepPowerDown = 0xAB,
    DeepPowerDown = 0xB9
  };
  static constexpr uint16_t pageSize = 256;

  static constexpr size_t memorySize{0x400000};
  const std::string &memoryFilePath;

  Identification device_id;
  std::fstream memoryFile;
};
}
}
}
