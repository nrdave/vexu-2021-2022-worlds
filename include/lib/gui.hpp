#pragma once
#include "pros/apix.h"
#include "stdio.h"
/**
 * The header file for the GUI namespace. The GUI uses a namespace rather
 * than a class due to the nature of the LittleVGL C graphics library. I've
 * tried using classes, but they run into too many issues with LVGL functions
 * 
 * The GUI namespace contains functions that perform all of the necessary tasks for 
 * creating a LVGL object.
 */ 

namespace GUI {

    /**
     * A function to create an LVGL button object. It packages all the LVGL functions to create,
     * set the press type and action, and align a button into one function, as well as handling
     * the creation of a label for the button
     * 
     * @param parent: the LVGL object the image should be created in
     * @param pressType: the button press type (Click, hold, long press, etc.)
     * @param function: the function to be called when the button is triggered
     * @param text: the label text on the button
     * @param align: the LVGL alignment type, aligns relative to the parent object
     * @param xCoord: the x coordinate offset from the given alignment
     * @param yCoord: the y coordinate offset from the given alignment
     * @param width: the width of the button 
     * @param height: the height of the button  
     * 
     * @return A pointer to a new LVGL button created using the given specs   
     */ 
    lv_obj_t * createButton(lv_obj_t * parent, lv_btn_action_t pressType, lv_action_t function,
                            const char* text, lv_align_t align, lv_coord_t xCoord, 
                            lv_coord_t yCoord, lv_coord_t width, lv_coord_t height);


    /**
     * A function to create an LVGL label object. It packages all the LVGL functions to create,
     * align, and set the text of a label
     * 
     * @param parent: the LVGL object the image should be created in
     * @param text: the text of the label
     * @param align: the LVGL alignment type, aligns relative to the parent object
     * @param xCoord: the x coordinate offset from the given alignment
     * @param yCoord: the y coordinate offset from the given alignment
     * 
     * @return A pointer to a new LVGL label created using the given specs   
     */ 
    lv_obj_t * createLabel(lv_obj_t * parent, const char* text, lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord);

    /**
     * A function to create an LVGL button matrix object. It packages all the LVGL functions to 
     * create, set the character map of, and align and size the button matrix into one function
     * 
     * @param parent: the LVGL object the image should be created in
     * @param map: a pointer to a String array used to generate the matrix of
     *             buttons and their labels
     * @param function: the function to be called when a button in the matrix is clicked
     * @param align: the LVGL alignment type, aligns relative to the parent object
     * @param xCoord: the x coordinate offset from the given alignment
     * @param yCoord: the y coordinate offset from the given alignment
     * @param width: the width of the button matrix
     * @param height: the height of the button matrix
     * 
     * @return A pointer to a new LVGL button matrix created using the given specs        
     */ 
    lv_obj_t * createButtonMatrix(lv_obj_t * parent, const char* map[], lv_btnm_action_t function,
                                  lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord,
                                  lv_coord_t width, lv_coord_t height);

}