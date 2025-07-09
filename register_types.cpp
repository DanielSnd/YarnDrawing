#include "register_types.h"

#include "core/object/class_db.h"
#include "ydrawing.h"

void initialize_ydrawing_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<YDrawing>();
}

void uninitialize_ydrawing_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
   // Nothing to do here in this example.
}
