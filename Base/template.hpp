#include <iostream>
#include <memory>
#include <type_traits>

//这是一个通用型单例模板
template <class T>
class Singleton {
	public:
		Singleton() = delete;
		template<class... Args>
		static std::shared_ptr<T> getInstance(Args&&... args) {
			//C++11静态对象赋值的时候能保证线程安全，这里不用上锁
			if (!m_pInstance)
				m_pInstance = std::make_shared<T>(std::forward<Args>(args)...);
			return m_pInstance;
		}
private:
	static std::shared_ptr<T> m_pInstance;
};
template<class T>
std::shared_ptr<T> Singleton<T>::m_pInstance = nullptr;

void TestSingleton() {
	auto p1 = Singleton<int>::getInstance(10);
	std::cout << p1 << std::endl;
	auto p2 = Singleton<int>::getInstance(20);
	std::cout << p2 << std::endl;
	//模板变了编译器就会另外特化一个类出来，不会和之前冲突
	auto p3 = Singleton<std::string>::getInstance("1234");
	std::cout << p3 << std::endl;
}

void TestSimpleTraits() {
	std::cout << std::integral_constant<int, 20>::value << std::endl;
}