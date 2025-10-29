#ifndef BE_LAYER 
#define BE_LAYER 


typedef void (*BeLayerUpdateFunc)(float _dt, float _unscaledDt);
typedef void (*BeLayerInitFunc)();
struct BeLayer{
BeLayerUpdateFunc onUpdate;
BeLayerUpdateFunc onFixedUpdate;
BeLayerInitFunc onInit;

};


#endif 
