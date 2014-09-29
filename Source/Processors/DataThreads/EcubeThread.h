/*
------------------------------------------------------------------

This file is part of the Open Ephys GUI
Copyright (C) 2013 Open Ephys
Copyright (C) 2013 Michael Borisov

------------------------------------------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef __ECUBETHREAD_H_EC4CAD67__
#define __ECUBETHREAD_H_EC4CAD67__


#include "../../../JuceLibraryCode/JuceHeader.h"

#include <stdio.h>
#include <string.h>

#include "DataThread.h"
#include "../GenericProcessor/GenericProcessor.h"

#define MAX_NUM_DATA_STREAMS 8

class SourceNode;

#if JUCE_WINDOWS
#ifdef ECUBE_SUPPORT
#define ECUBE_COMPILE
#endif
#endif

#ifdef ECUBE_COMPILE
class EcubeDevInt;
#endif

class EcubeThread : public DataThread

{
public:

#ifdef ECUBE_COMPILE
    EcubeThread(SourceNode* sn);
    ~EcubeThread();

    void run(); // Overridden

    /** Fills the DataBuffer with incoming data. This is the most important
    method for each DataThread.*/
    virtual bool updateBuffer();

    /** Returns true if the data source is connected, false otherwise.*/
    virtual bool foundInputSource();

    /** Initializes data transfer.*/
    virtual bool startAcquisition();

    /** Stops data transfer.*/
    virtual bool stopAcquisition();

    /** Returns the number of continuous channels the data source can provide.*/
    virtual int getNumChannels();

    /** Returns the sample rate of the data source.*/
    virtual float getSampleRate();

    /** Returns the volts per bit of the data source.*/
    virtual float getBitVolts();

    virtual void getChannelsInfo(StringArray &Names, Array<channelType> &type, Array<int> &stream, Array<int> &originalChannelNumber, Array<float> &gains);
    void setDefaultNamingScheme(int scheme);


private:
    void setDefaultChannelNamesAndType();

    // used for data stream names...
    int numberingScheme;
    StringArray Names;
    Array<channelType> type;
    Array<float> gains;
    Array<int> stream;
    Array<int> originalChannelNumber;

    ScopedPointer<EcubeDevInt> pDevInt;

    float m_samplerate;
    bool acquisition_running;

#else
/** Empty methods for non-Windows platforms **/
bool updateBuffer() {}
bool foundInputSource() {}
bool startAcquisition() {}
bool stopAcquisition() {}
int getNumChannels() {}
float getSampleRate() {}
float getBitVolts() {}

#endif



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EcubeThread);
};

#endif  // __RHD2000THREAD_H_2C4CBD67__
