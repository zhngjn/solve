#include <memory>
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

namespace impl1
{
class ResourceManager {
public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ~ResourceManager() {
        std::cout << "Destruct ResourceManager..." << std::endl;
    }

    void Count() {
        std::cout << "Counter=" << counter_++ << std::endl;
    }

    static std::shared_ptr<ResourceManager> GetInstance() {
        if (gInstance == nullptr) {
            gInstance = std::shared_ptr<ResourceManager>(new ResourceManager());
        }
        return gInstance;
    }

private:
    ResourceManager() {
        std::cout << "Construct ResourceManager..." << std::endl;
    }

private:
    int counter_ = 0;

    static std::shared_ptr<ResourceManager> gInstance;
};
std::shared_ptr<ResourceManager> ResourceManager::gInstance = nullptr;
} // namespace impl1

namespace impl2
{
class ResourceManager {
public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ~ResourceManager() {
        std::cout << "Destruct ResourceManager..." << std::endl;
    }

    void Count() {
        std::lock_guard<std::mutex> lock(mtx_);
        std::cout << "Counter=" << counter_++ << std::endl;
    }

    static std::shared_ptr<ResourceManager> GetInstance() {
        if (gInstance == nullptr) {
            std::lock_guard<std::mutex> lock(gMtx);
            if (gInstance == nullptr) {
                gInstance = std::shared_ptr<ResourceManager>(new ResourceManager());
            }
        }
        return gInstance;
    }

private:
    ResourceManager() {
        std::cout << "Construct ResourceManager..." << std::endl;
    }

private:
    int counter_ = 0;
    std::mutex mtx_;

    static std::shared_ptr<ResourceManager> gInstance;
    static std::mutex gMtx;
};
std::shared_ptr<ResourceManager> ResourceManager::gInstance = nullptr;
std::mutex ResourceManager::gMtx;
} // namespace impl2

namespace impl3
{
class ResourceManager {
public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ~ResourceManager() {
        std::cout << "Destruct ResourceManager..." << std::endl;
    }

    void Count() {
        std::lock_guard<std::mutex> lock(mtx_);
        std::cout << "Counter=" << counter_++ << std::endl;
    }

    static std::shared_ptr<ResourceManager> GetInstance() {
        std::call_once(gFlag, ResourceManager::InitInstance);
        return gInstance;
    }

private:
    ResourceManager() {
        std::cout << "Construct ResourceManager..." << std::endl;
    }

    static void InitInstance() {
        gInstance = std::shared_ptr<ResourceManager>(new ResourceManager());
    }

private:
    int counter_ = 0;
    std::mutex mtx_;

    static std::shared_ptr<ResourceManager> gInstance;
    static std::once_flag gFlag;
};
std::shared_ptr<ResourceManager> ResourceManager::gInstance = nullptr;
std::once_flag ResourceManager::gFlag;
} // namespace impl3

namespace impl4
{
class ResourceManager {
public:
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ~ResourceManager() {
        std::cout << "Destruct ResourceManager..." << std::endl;
    }

    void Count() {
        std::lock_guard<std::mutex> lock(mtx_);
        std::cout << "Counter=" << counter_++ << std::endl;
    }

    static ResourceManager& GetInstance() {
        static ResourceManager gInstance;
        return gInstance;
    }

private:
    ResourceManager() {
        std::cout << "Construct ResourceManager..." << std::endl;
    }

private:
    int counter_ = 0;
    std::mutex mtx_;
};
} // namespace impl4

namespace impl5
{
template <typename T>
class Singleton {
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    ~Singleton() {
        std::cout << "Destruct Singleton..." << std::endl;
    }

    void Count() {
        std::cout << T::Type() << " Counter=" << counter_++ << std::endl;
    }

    static T& GetInstance() {
        static T gInstance;
        return gInstance;
    }

protected:
    Singleton() {
        std::cout << "Construct Singleton..." << std::endl;
    }

private:
    int counter_ = 0;
};

class DeviceManager : public Singleton<DeviceManager> {
private:
    friend class Singleton<DeviceManager>;
public:
    ~DeviceManager() {
        std::cout << "Destruct DeviceManager..." << std::endl;
    }

    static std::string Type() {
        return "Device";
    }

private:
    DeviceManager() {
        std::cout << "Construct DeviceManager..." << std::endl;
    }
};

class DataManager : public Singleton<DataManager> {
private:
    friend class Singleton<DataManager>;
public:
    ~DataManager() {
        std::cout << "Destruct DataManager..." << std::endl;
    }

    static std::string Type() {
        return "Data";
    }

private:
    DataManager() {
        std::cout << "Construct DataManager..." << std::endl;
    }
};
} // namespace impl5

namespace impl6
{
class DeviceManager {
public:
    void Count() {
        std::cout << "Device Counter=" << counter_++ << std::endl;
    }

private:
    int counter_ = 0;
};

class DataManager {
public:
    void Count() {
        std::cout << "Data Counter=" << counter_++ << std::endl;
    }

private:
    int counter_ = 0;
};

template <typename T>
T& GetGlobal() {
    static T instance;
    return instance;
}
} // namespace impl6

void Test1() {
    using namespace impl1;
    ResourceManager::GetInstance()->Count();
    ResourceManager::GetInstance()->Count();
    ResourceManager::GetInstance()->Count();
}

void Test2() {
    using namespace impl2;

    auto Run = [](){
        ResourceManager::GetInstance()->Count();
    };

    std::thread threads[10];
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(Run);
    for (auto& thread : threads)
        thread.join();
}

void Test3() {
    using namespace impl3;

    auto Run = [](){
        ResourceManager::GetInstance()->Count();
    };

    std::thread threads[10];
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(Run);
    for (auto& thread : threads)
        thread.join();
}

void Test4() {
    using namespace impl4;
    std::thread threads[10];

    auto Run = [](){
        ResourceManager::GetInstance().Count();
    };

    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(Run);
    for (auto& thread : threads)
        thread.join();
}

void Test5() {
    using namespace impl5;
    DeviceManager::GetInstance().Count();
    DataManager::GetInstance().Count();
    DeviceManager::GetInstance().Count();
    DataManager::GetInstance().Count();
}

void Test6() {
    using namespace impl6;
    GetGlobal<DeviceManager>().Count();
    GetGlobal<DataManager>().Count();
    GetGlobal<DeviceManager>().Count();
    GetGlobal<DataManager>().Count();
}

int main() {
    std::vector<void(*)()> tests = {&Test1, &Test2, &Test3, &Test4, &Test5, &Test6};
    int i = 0;
    for (auto test : tests) {
        std::cout << "#Test Case " << ++i << std::endl;
        (*test)();
    }
}
