#pragma once

#include <cstdint>

namespace hal {

enum class GpioDirection { Input, Output };
enum class GpioEdge { None, Rising, Falling, Both };

struct GpioConfig {
  uint8_t pin = 0;
  GpioDirection direction = GpioDirection::Input;
  bool active_low = false;
  GpioEdge edge_trigger = GpioEdge::None;
};

/// Abstract GPIO interface for interrupts and control.
class IGpioInterface {
 public:
  virtual ~IGpioInterface() = default;

  virtual void open() = 0;
  virtual void close() = 0;
  virtual bool isOpen() const = 0;

  virtual bool read() = 0;
  virtual void write(bool value) = 0;

  /// Wait for configured edge (e.g. SPI frame ready).
  virtual bool waitForEdge(uint32_t timeout_ms = 0) = 0;
};

}  // namespace hal
