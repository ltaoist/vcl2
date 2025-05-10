/* comment */
#ifndef INCLUDED_VCL_FLTCALL_HXX
#define INCLUDED_VCL_FLTCALL_HXX

class FilterConfigItem;
class SvStream;
class Graphic;

typedef bool (*PFilterCall)(SvStream & rStream, Graphic & rGraphic,
                            FilterConfigItem* pConfigItem);
    // Of this type are both export-filter and import-filter functions
    // rFileName is the complete path to the file to be imported or exported
    // pCallBack can be NULL. pCallerData is handed to the callback function
    // pOptionsConfig can be NULL; if not, the group of the config is already set
    // and may not be changed by this filter!

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
