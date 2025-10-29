// Interface for anything that notifies observers
#pragma once
#include <vector>
#include <algorithm>
#include "IObserver.h"

// Base subject: Anything that can observe should inherit from this class
class ISubject {
public:
  virtual ~ISubject() = default;

  virtual void addObserver(IObserver* observer) {
    if (!observer) return;
    observers.push_back(observer);
  }

  virtual void removeObserver(IObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
  }

protected:
  void notifyAll() {
    for (auto* observer : observers) {
      if (observer) {
        observer->update();
      }
    }
  }

private:
  std::vector<IObserver*>observers;
  };