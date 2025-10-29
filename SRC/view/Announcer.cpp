#include "view/Announcer.h"
#include <stdexcept>

Announcer::Announcer(Board& board) : board_(board) {
  board_.addObserver(this);
  initVoice();
}

Announcer::~Announcer() {
  board_.removeObserver(this);
  CoUninitialize();     // Needed to close the COM library for the thread
}

bool Announcer::initVoice() {
  HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
  if (FAILED(hr) && hr != RPC_E_CHANGED_MODE)
    return false;

  // Create the SAPI voice object; ComPtr takes ownership automatically.
  hr = CoCreateInstance(CLSID_SpVoice, nullptr, CLSCTX_ALL,
    IID_ISpVoice, &voice_);
  return SUCCEEDED(hr) && voice_;
}

void Announcer::speak(const std::wstring& msg) {
  if (!voice_) return;
  voice_->Speak(msg.c_str(), SPF_ASYNC, nullptr);
}

void Announcer::update() {
  speak(L"Board updated.");
}
