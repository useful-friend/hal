#include "hal/factory.hpp"
#include "hal/i2c_interface.hpp"
#include <memory>
#include <stdexcept>

namespace hal {

class Ft4222I2c : public II2cInterface {
 public:
  explicit Ft4222I2c(const I2cConfig& config);
  ~Ft4222I2c() override;

  void open() override;
  void close() override;
  bool isOpen() const override { return open_; }

  void write(std::span<const uint8_t> data) override;
  void read(std::span<uint8_t> data) override;
  void writeRead(std::span<const uint8_t> write_data,
                 std::span<uint8_t> read_data) override;
  bool waitIdle(float timeout_s = 0.5f) override;

 private:
  I2cConfig config_;
  bool open_ = false;
  void* handle_ = nullptr;
};

Ft4222I2c::Ft4222I2c(const I2cConfig& config) : config_(config) {}

Ft4222I2c::~Ft4222I2c() { close(); }

void Ft4222I2c::open() {
  // TODO: Link libft4222, FT4222_I2CMaster_Init
  open_ = true;
}

void Ft4222I2c::close() {
  if (!open_) return;
  open_ = false;
}

void Ft4222I2c::write(std::span<const uint8_t> data) {
  if (!open_) throw std::runtime_error("I2C not open");
  (void)data;
}

void Ft4222I2c::read(std::span<uint8_t> data) {
  if (!open_) throw std::runtime_error("I2C not open");
  (void)data;
}

void Ft4222I2c::writeRead(std::span<const uint8_t> write_data,
                          std::span<uint8_t> read_data) {
  if (!open_) throw std::runtime_error("I2C not open");
  (void)write_data;
  (void)read_data;
}

bool Ft4222I2c::waitIdle(float timeout_s) {
  if (!open_) return false;
  (void)timeout_s;
  return true;
}

std::unique_ptr<II2cInterface> createFt4222I2c(const I2cConfig& config) {
  return std::make_unique<Ft4222I2c>(config);
}

}  // namespace hal
