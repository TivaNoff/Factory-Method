#include <iostream>
#include <memory>
#include <string>

// Базовий інтерфейс транспорту
class Transport {
public:
    virtual ~Transport() = default;
    virtual void deliver() const = 0;
};

// Конкретний транспорт: Вантажівка
class Truck : public Transport {
public:
    void deliver() const override {
        std::cout << "Delivering by truck over land." << std::endl;
    }
};

// Конкретний транспорт: Корабель
class Ship : public Transport {
public:
    void deliver() const override {
        std::cout << "Delivering by ship over sea." << std::endl;
    }
};

// Абстрактна логістика, що оголошує фабричний метод
class Logistics {
public:
    virtual ~Logistics() = default;
    // Фабричний метод, який створює транспорт
    virtual std::unique_ptr<Transport> createTransport() const = 0;

    // Універсальний метод доставки
    void planDelivery() const {
        // Використовуємо фабричний метод, щоб отримати необхідний транспорт
        auto transport = createTransport();
        transport->deliver();
    }
};

// Конкретна логістика: Дорожня
class RoadLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() const override {
        return std::make_unique<Truck>();
    }
};

// Конкретна логістика: Морська
class SeaLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() const override {
        return std::make_unique<Ship>();
    }
};

int main() {
    // Використовуємо дорожню логістику
    std::unique_ptr<Logistics> roadLogistics = std::make_unique<RoadLogistics>();
    roadLogistics->planDelivery();  // Виведе: Delivering by truck over land.

    // Використовуємо морську логістику
    std::unique_ptr<Logistics> seaLogistics = std::make_unique<SeaLogistics>();
    seaLogistics->planDelivery();   // Виведе: Delivering by ship over sea.

    return 0;
}
