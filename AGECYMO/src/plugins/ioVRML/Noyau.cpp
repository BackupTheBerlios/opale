// Libraries.
#include <cstdlib>
#include <dlfcn.h>
#include <iostream>
using namespace std;

// Allow to save the plugin.
typedef char * (*functionQuery) (void);
typedef int (*functionRun) (void);

const char * PLUGIN_NAME = "./libReadVRML.plg.so";


// Main function.
int main(int argc, char *argv[]) {

  // Version checking.
#if __GNUC__ == 3 
  void *handle = dlopen(PLUGIN_NAME, RTLD_NOW | RTLD_GLOBAL);
#else
  void *handle = dlopen(PLUGIN_NAME, RTLD_NOW);
#endif

  // If the library doesn't exist.
  if (! handle) {
    cerr << "Library not found\n";
    return EXIT_FAILURE;
  }
  

  // Function query using.
  functionQuery query = (functionQuery) dlsym(handle, "query");

  if (! query) {
    cerr << "Function \"query\" not found\n";
    return EXIT_FAILURE;
  }

  //char *pluginName = query();

  // Function run using.
  functionRun run = (functionRun) dlsym(handle, "run");

  if (! run) {
    cerr << "Function \"run\" not found\n";
    return EXIT_FAILURE;
  }
  
  int returnCode = run();

  // Handle closing.
  dlclose(handle);
  
  return returnCode;

}


  
  
