/* comment */
#ifndef INCLUDED_VCL_INC_OSX_SALNATIVEWIDGETS_H
#define INCLUDED_VCL_INC_OSX_SALNATIVEWIDGETS_H

#define TAB_HEIGHT 20             // height of tab header in pixels
#define TAB_TEXT_MARGIN 12        // left/right margin of text within tab headers

#define FOCUS_RING_WIDTH 4  // width of focus ring in pixels

#define MEDIUM_PROGRESS_INDICATOR_HEIGHT 10  // height of medium progress indicator in pixels
#define LARGE_PROGRESS_INDICATOR_HEIGHT 16   // height of large progress indicator in pixels

#define PUSH_BUTTON_NORMAL_HEIGHT 21  // height of normal push button without focus ring in pixels
#define PUSH_BUTTON_SMALL_HEIGHT 15   // height of small push button without focus ring in pixels

#define RADIO_BUTTON_SMALL_SIZE 14     // width/height of small radio button without focus ring in pixels
#define RADIO_BUTTON_TEXT_SEPARATOR 3  // space between radio button and following text in pixels

#define CHECKBOX_SMALL_SIZE 14     // width/height of checkbox without focus ring in pixels
#define CHECKBOX_TEXT_SEPARATOR 3  // space between checkbox and following text in pixels

#define SLIDER_WIDTH 19   // width of slider in pixels
#define SLIDER_HEIGHT 18  // height of slider in pixels

#define EDITBOX_HEIGHT 21       // height of editbox without focus ring in pixels
#define EDITBOX_BORDER_WIDTH 1  // width of editbox border in pixels
#define EDITBOX_INSET_MARGIN 1  // width of left/right as well as top/bottom editbox margin in pixels

#define COMBOBOX_HEIGHT 20        // height of combobox without focus ring in pixels
#define COMBOBOX_BUTTON_WIDTH 18  // width of combobox button without focus ring in pixels
#define COMBOBOX_BORDER_WIDTH 1   // width of combobox border in pixels
#define COMBOBOX_TEXT_MARGIN 1    // left/right margin of text in pixels

#define LISTBOX_HEIGHT 20        // height of listbox without focus ring in pixels
#define LISTBOX_BUTTON_WIDTH 18  // width of listbox button without focus ring in pixels
#define LISTBOX_BORDER_WIDTH 1   // width of listbox border in pixels
#define LISTBOX_TEXT_MARGIN 1    // left/right margin of text in pixels

#define SPIN_BUTTON_WIDTH 13         // width of spin button without focus ring in pixels
#define SPIN_UPPER_BUTTON_HEIGHT 11  // height of upper spin button without focus ring in pixels
#define SPIN_LOWER_BUTTON_HEIGHT 11  // height of lower spin button without focus ring in pixels

// FIXME: spinboxes are positioned one pixel shifted to the right by VCL. As positioning as well as size should be equal to
// corresponding editboxes, comboboxes or listboxes, positioning of spinboxes should by equal too. Issue cannot be fixed within
// native widget drawing code. As a workaround, an offset is considered for spinboxes to align spinboxes correctly.

#define SPINBOX_OFFSET 1  // left offset for alignment with editboxes, comboboxes, and listboxes

#endif // INCLUDED_VCL_INC_OSX_SALNATIVEWIDGETS_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
