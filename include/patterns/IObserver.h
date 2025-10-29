// Interface for anything that listens for updates
#pragma once

class IObserver {
public:
  virtual ~IObserver() = default;
  virtual void update() = 0;
};