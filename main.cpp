#include <array>
#include <forward_list>
#include <functional>
#include <iostream>

// This defines the actual events that can be emitted.
enum class BWE_EVENT {
    INCREASE,
    DECREASE,
    NUM_EVENT_TYPES,  // This must be last, it's a trick for counting the number
                    // of enum elements.
};

template <BWE_EVENT T>
struct BweEventHandlerInfo {
    // This base case will cause a compile error for any BWE_EVENT types that
    // haven't been specialized and therefore don't have an Args signature.
};

// This is the only thing you need to write, one specialization for each event
// type.
template <>
struct BweEventHandlerInfo<BWE_EVENT::INCREASE> {
    struct Args {
        int a;
        int b;
    };
};

template <>
struct BweEventHandlerInfo<BWE_EVENT::DECREASE> {
    struct Args {
        float a;
        float b;
    };
};

// This base class exists so that the EventEmitter has object instances to
// store.
struct HandlerStorageBase {
    virtual ~HandlerStorageBase() = default;
    virtual void Handle(void* args) = 0;
};

// This implementation of HandlerStorageBase is resolved by the virtual function
// pointer and calls the actual function that EventEmitter callers originally
// registered.
template <BWE_EVENT T>
struct HandlerStorage : public HandlerStorageBase {
    using EventArgsType = typename BweEventHandlerInfo<T>::Args;
    using HandlerType = std::function<void(EventArgsType*)>;

    HandlerStorage(HandlerType handler) : handler_(handler) {}

    ~HandlerStorage() override = default;

    // The function arg here can be char* instead. The idea is to have it a single
    // generic pointer, which we can convert to the real type in a type safe way,
    // since this templated structure knows the real type.
    void Handle(void* args) override {
        handler_(reinterpret_cast<EventArgsType*>(args));
    }

private:
    HandlerType handler_;
};

// This is the event emitter class.
struct EventEmitter {
    EventEmitter() = default;

    template <BWE_EVENT T>
    void Subscribe(typename HandlerStorage<T>::HandlerType handler) {
        handlers_[static_cast<std::size_t>(T)] =
                std::make_unique<HandlerStorage<T>>(handler);
    }

    template <BWE_EVENT T>
    void Emit(typename HandlerStorage<T>::EventArgsType* args) {
        handlers_[static_cast<std::size_t>(T)]->Handle(args);
    }

    std::array<std::unique_ptr<HandlerStorageBase>,
               (size_t)BWE_EVENT::NUM_EVENT_TYPES>
            handlers_;
};

int main() {
    EventEmitter emitter;

    auto funcIncrease = [](BweEventHandlerInfo<BWE_EVENT::INCREASE>::Args* args) {
        std::cout << "a=" << args->a << " b=" << args->b << std::endl;
    };

    emitter.Subscribe<BWE_EVENT::INCREASE>(funcIncrease);

    auto funcDecrease = [](BweEventHandlerInfo<BWE_EVENT::DECREASE>::Args* args) {
        std::cout << "a=" << args->a << " b=" << args->b << std::endl;
    };

    emitter.Subscribe<BWE_EVENT::DECREASE>(funcDecrease);

    BweEventHandlerInfo<BWE_EVENT::INCREASE>::Args args = {
            .a = 2,
            .b = 3,
    };

    BweEventHandlerInfo<BWE_EVENT::DECREASE>::Args argsDecrease = {
            .a = 6.5,
            .b = 7.8,
    };

    std::cout << "This should invoke the increase handler." << std::endl;
    emitter.Emit<BWE_EVENT::INCREASE>(&args);

    std::cout << "This should invoke the decrease handler." << std::endl;
    emitter.Emit<BWE_EVENT::DECREASE>(&argsDecrease);
}