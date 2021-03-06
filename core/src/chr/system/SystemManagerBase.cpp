#include "chr/system/SystemManagerBase.h"
#include "chr/cross/Context.h"

using namespace std;

namespace chr
{
  namespace system
  {
    const string& platformName()
    {
      static const string PLATFORM_NAMES[5] = { "OSX", "iOS", "Android", "Emscripten", "Windows" };
      return PLATFORM_NAMES[CHR_PLATFORM];
    }

    // ---
    
    const Info& ManagerBase::getInfo() const
    {
      return info;
    }
    
    void ManagerBase::updateInfo()
    {
      info.platformString = platformName();
      
      info.osVersion = getOsVersion();
      info.osVersionString = getOsVersionString();
      
      info.deviceString = getDeviceString();
    }
  }
  
  SystemInfo getSystemInfo()
  {
    return systemManager().getInfo();
  }
}
