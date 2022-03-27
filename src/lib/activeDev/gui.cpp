#include "main.h"

/**
 * The implementations for the GUI namespace functions, along with the
 * declarations of all LVGL objects used.
 * The functions initialize LVGL objects or handle
 * event triggers from those objects.
 */

lv_obj_t * GUI::createButton(lv_obj_t * parent, lv_btn_action_t pressType, lv_action_t function,
                             const char* text, lv_align_t align, 
                             lv_coord_t xCoord, lv_coord_t yCoord,
                             lv_coord_t width, lv_coord_t height)
{
    //Creating an LVGL button
    lv_obj_t * btn = lv_btn_create(parent, NULL);
    //Setting the button's action upon a given type of trigger
    lv_btn_set_action(btn, pressType, function);   
    //Aligning the button relative to its parent
    lv_obj_align(btn, NULL, align, xCoord, yCoord);
    //Setting the button's size
    lv_obj_set_size(btn, width, height);
    //Creating a label for the button
    lv_obj_t * label = createLabel(btn, text, LV_ALIGN_CENTER, 0, 0);
    /**
     * Return the created button
     * This returns the button to the declared LVGL object in
     * initialize, making that object into an identical button to 
     * the button btn created in this function.
     */ 
    return btn;
}

lv_obj_t * GUI::createLabel(lv_obj_t * parent, const char* text, lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord)
{
    //Creating a LVGL Label
    lv_obj_t * lbl = lv_label_create(parent, NULL);
    //Aligning the label relative to its parent
    lv_obj_align(lbl, NULL, align, xCoord, yCoord);
    //Setting the label's text
    lv_label_set_text(lbl, text);  
    /**
     * Return the created label
     * This returns the label to the declared LVGL object in
     * initialize, making that object into an identical label to 
     * the label lbl created in this function.
     */ 
    return lbl;
}

lv_obj_t * GUI::createButtonMatrix(lv_obj_t * parent, const char* map[], lv_btnm_action_t function,
                                   lv_align_t align, lv_coord_t xCoord, lv_coord_t yCoord, 
                                   lv_coord_t width, lv_coord_t height)
{
    //Creating an LVGL button matrix
    lv_obj_t * btnm = lv_btnm_create(parent, NULL);
    //Setting the button matrix's action upon a given type of trigger
    lv_btnm_set_action(btnm, function);   
    //Set the String array to be used to create the button matrix
    lv_btnm_set_map(btnm, map);
    //Aligning the button matrix relative to its parent
    lv_obj_align(btnm, NULL, align, xCoord, yCoord);
    //Setting the size of the button matrix
    lv_obj_set_size(btnm, width, height);
    /**
     * Return the created button matrix
     * This returns the button matrix to the declared LVGL object in
     * initialize, making that object into an identical button matrix to 
     * the button matrix btnm created in this function.
     */ 
    return btnm;
}
lv_obj_t * GUI::createScreen()
{
    /**
     * This function merely hides the calling of lv_obj_create(NULL, NULL)
     * so the function itself just creates a screen and returns it
     */ 
    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    return scr;
}

lv_res_t GUI::updateAutonID(lv_obj_t * btnm, const char * txt){
    /**
     * Running the current selected button in the matrix through a
     * series of if-else-if statements to determine which autonomous
     * routine is selected. If there are any issues, the function
     * defaults to no autonomous
     */ 
    if(txt == "Test") autonID = Auton::test;
    else if(txt == "None") autonID = Auton::none;
    else if(txt == "Skills") autonID = Auton::skills;
    else if(txt == "Left") autonID = Auton::left;
    else if(txt == "Mid to Left") autonID = Auton::midleft;
    else if(txt == "Right") autonID = Auton::right;
    else if(txt == "Mid to Right") autonID = Auton::midright;
    else autonID = Auton::none;
    //Updating the label for the current selected autonomous
    updateAutonLbl();
    return LV_RES_OK;
}

void GUI::updateAutonLbl()
{
    /**
     * Using autonID as a switch, the function determines
     * the current autonomous routine selected and sets 
     * the current Autonomous label to the corresponding
     * text
     */ 
    switch(autonID)
    {
        case Auton::test:
            lv_label_set_text(curAutonLbl, "Test");
            break;
        case Auton::skills:
            lv_label_set_text(curAutonLbl, "Skills");
            break;
        case Auton::left:
            lv_label_set_text(curAutonLbl, "Left Corner");
            break;
        case Auton::midleft:
            lv_label_set_text(curAutonLbl, "Middle + Left Corner");
            break;
        case Auton::right:
            lv_label_set_text(curAutonLbl, "Right Corner");
            break;
        case Auton::midright:
            lv_label_set_text(curAutonLbl, "Middle + Right Corner");
            break;
        case Auton::none:
            lv_label_set_text(curAutonLbl, "No Auton Selected");
            break;
    }
}

lv_res_t GUI::updateTelemetryData(lv_obj_t * btnm, const char* txt)
{

    lv_label_set_text(debugData1, "No Data Selected");
    lv_label_set_text(debugData2, "No Data Selected"); 
    return LV_RES_OK;
}

void GUI::updateTelemetryLabel(lv_obj_t * label, Telemetry t)
{   
    /**
     * Creating char arrays to hold the rounded data for each telemetry value
     * I do this to cut the size of the data, rather than
     * printing every character, which includes a lot of zeros at the end
     * The arrays are 30 characters in order to include the labels for each data value
     */ 
    char pos[30]; 
    char targPos[30]; 
    char velo[30]; 
    char targVelo[30]; 
    char temp[30]; 
    char torque[30]; 
    //Creating a char[] to write the output to
    char output[256];
    //Printing the Telemetry values to their respective arrays
    snprintf(pos, 30, "Position: %f", t.pos);
    snprintf(targPos, 30, "Target Position: %f", t.targetPos);
    snprintf(velo, 30, "Velocity: %f", t.velo);
    snprintf(targVelo, 30, "Target Velocity%f", t.targetVelo);
    snprintf(temp, 30, "Temperature: %f", t.temp);
    snprintf(torque, 30, "Torque %f", t.torque);
    //Printing the shortened telemetry values to the output array
    snprintf(output, 256, "%s%s\n%s%s\n%s%s", pos, targPos, velo, targVelo, temp, torque);
    //Setting the text on the label
    lv_label_set_text(label, output);
}
/**
 * LVGL doesn't allow functions with parameters to be a callback function for a
 * button action, so I had to wrap a few functions, such as lv_scr_load(), which loads a screen,
 * in a format that the lv_btn_set_action() function would accept
 */ 
lv_res_t GUI::goToAuton(lv_obj_t * btn)
{
    lv_scr_load(scrAuton);
    return LV_RES_OK;
}

lv_res_t GUI::goToMain(lv_obj_t * btn)
{
    lv_scr_load(scrMain);
    return LV_RES_OK;
}

lv_res_t GUI::goToDebug(lv_obj_t * btn)
{
    lv_scr_load(scrDebug);
    return LV_RES_OK;
}

lv_res_t GUI::runAuton(lv_obj_t * btn)
{
    autonomous();
    return LV_RES_OK;
}