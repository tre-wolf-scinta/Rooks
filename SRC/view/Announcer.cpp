#include "view/Announcer.h"
#include <combaseapi.h>

Announcer::Announcer(Board& board)
  : board_(board)
{
  initVoice();
  speak(L"Game started.");
}

Announcer::~Announcer() {
  cleanupVoice();
}

void Announcer::update() {
  // Observer hook (unused for now)
}

void Announcer::speak(const std::wstring& msg) {
  if (!voice_) return;
  voice_->Speak(msg.c_str(), SPF_ASYNC, nullptr);
}

bool Announcer::initVoice() {
  HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
  if (FAILED(hr) && hr != RPC_E_CHANGED_MODE) {
    return false;
  }

  hr = ::CoCreateInstance(CLSID_SpVoice, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&voice_));
  if (FAILED(hr)) {
    voice_.Reset();
    return false;
  }
  return true;
}

void Announcer::cleanupVoice() {
  voice_.Reset();
  CoUninitialize();
}