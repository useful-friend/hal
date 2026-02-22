#pragma once

#include <cstdint>
#include <memory>
#include <span>
#include <vector>

namespace hal {

struct SpiConfig {
  uint32_t clock_hz = 10'000'000;  // 10 MHz default
  uint8_t mode = 0;                 // CPOL=0, CPHA=0
  uint8_t bits_per_word = 8;
  uint8_t chip_select = 0;
};

/// Abstract SPI interface for hardware abstraction.
/// Implementations: FT4222, Linux spidev, mock for testing.
class ISpiInterface {
 public:
  virtual ~ISpiInterface() = default;

  virtual void open() = 0;
  virtual void close() = 0;
  virtual bool isOpen() const = 0;

  /// Full-duplex transfer: send tx, receive into rx (same length).
  virtual void transfer(std::span<const uint8_t> tx, std::span<uint8_t> rx) = 0;

  /// Read-only: transmit zeros, receive into rx.
  virtual void read(std::span<uint8_t> rx) = 0;

  /// Write-only: send tx.
  virtual void write(std::span<const uint8_t> tx) = 0;
};

}  // namespace hal
