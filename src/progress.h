#pragma once

extern void uiSetupProgress(size_t stepCount);

/** Throws an exception when abortion is requested */
extern void uiAdvanceProgress(std::string stepName);

/** Progress is advanced each 50 frames when exporting animation */
const int checkProgressFrameInterval = 50;