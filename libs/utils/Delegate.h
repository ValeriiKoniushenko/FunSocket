#pragma once

#include "CopyableAndMoveable.h"

#include <functional>
#include <utility>
#include <vector>

template <class T, class CallbackT>
class Delegate : public Utils::CopyableAndMoveable
{
public:
	template <class... TArgs>
	void trigger(TArgs&&... args)
	{
		if (callback_ && objP)
		{
			std::invoke(callback_, objP, std::forward<TArgs>(args)...);
		}
	}

	void subscribe(T* obj, CallbackT&& callback)
	{
		callback_ = std::forward<CallbackT>(callback);
		objP = obj;
	}

	void reset()
	{
		callback_ = {};
		objP = {};
	}

private:
	CallbackT callback_{};
	T* objP{};
};

template <class F>
class LambdaDelegate : public Utils::CopyableAndMoveable
{
public:
	using CallbackT = std::function<F>;

	template <class... TArgs>
	void trigger(TArgs&&... args)
	{
		if (callback_)
		{
			std::invoke(callback_, std::forward<TArgs>(args)...);
		}
	}

	void subscribe(CallbackT&& callback)
	{
		callback_ = std::forward<CallbackT>(callback);
	}

	void reset()
	{
		callback_ = {};
	}

private:
	CallbackT callback_{};
};

template <class F>
class LambdaMulticastDelegate : public Utils::CopyableAndMoveable
{
public:
	using CallbackT = std::function<F>;

	template <class... TArgs>
	void trigger(TArgs&&... args)
	{
		for (auto& callback : callbacks_)
		{
			std::invoke(callback, std::forward<TArgs>(args)...);
		}
	}

	void subscribe(CallbackT&& callback)
	{
		callbacks_.emplace_back(std::forward<CallbackT>(callback));
	}

	void reset()
	{
		callbacks_.clear();
	}

private:
	std::vector<CallbackT> callbacks_{};
};