#ifndef CLASS_PLUGIN_H
#define CLASS_PLUGIN_H


enum PluginType{ LOAD_AND_SAVE, ACTION }; //What's the type of the plugin ?
  
enum CallType{ACTION_CALL, LOAD_CALL, SAVE_CALL}; 
  
class MenuAddOn
{
  public:
  CallType typeAppel;
  std::string *emplacement;
  std::string *image; //
  std::string *texte;
    
  ~MenuAddOn()
  {
    if (emplacement != NULL)
    {
      delete emplacement;
    }
      
    if (image != NULL)
    {
      delete image;
    }
      
    if (texte != NULL)
    {
      delete texte;
    }
  }
    
};
  


#endif
