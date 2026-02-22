#include "hal/factory.hpp"
#include "hal/spi_interface.hpp"
#include <stdexcept>
#include <vector>

namespace hal {

class Ft4222Spi : public ISpiInterface {
 public:
  explicit Ft4222Spi(const SpiConfig& config);
  ~Ft4222Spi() override;

  void open() override;
  void close() override;
  bool isOpen() const override { return open_; }

  void transfer(std::span<const uint8_t> tx, std::span<uint8_t> rx) override;
  void read(std::span<uint8_t> rx) override;
  void write(std::span<const uint8_t> tx) override;

 private:
  SpiConfig config_;
  bool open_ = false;
  void* handle_ = nullptr;
};

Ft4222Spi::Ft4222Spi(const SpiConfig& config) : config_(config) {}

Ft4222Spi::~Ft4222Spi() { close(); }

void Ft4222Spi::open() {
  // TODO: Link libft4222, FT4222_OpenEx, FT4222_SPIMaster_Init
  open_ = true;
}

void Ft4222Spi::close() {
  if (!open_) return;
  open_ = false;
}

void Ft4222Spi::transfer(std::span<const uint8_t> tx, std::span<uint8_t> rx) {
  if (!open_) throw std::runtime_error("SPI not open");
  if (tx.size() != rx.size())
    throw std::invalid_argument("SPI transfer: tx and rx size must match");
  (void)tx;
  (void)rx;
}

void Ft4222Spi::read(std::span<uint8_t> rx) {
  if (!open_) throw std::runtime_error("SPI not open");
  std::vector<uint8_t> zeros(rx.size(), 0);
  transfer(zeros, rx);
}

void Ft4222Spi::write(std::span<const uint8_t> tx) {
  if (!open_) throw std::runtime_error("SPI not open");
  std::vector<uint8_t> discard(tx.size());
  transfer(tx, discard);
}

std::unique_ptr<ISpiInterface> createFt4222Spi(const SpiConfig& config) {
  return std::make_unique<Ft4222Spi>(config);
}

}  // namespace hal
