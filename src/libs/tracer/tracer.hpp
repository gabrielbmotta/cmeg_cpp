// * @author   Juan GPC <jgarciaprietoh@mgh.harvard.edu>;


#ifndef TRACER_H
#define TRACER_H

//=============================================================================================================
// MACRO DEFINITIONS
//=============================================================================================================

#define TRACE

#ifdef TRACE
#define GP_TRACE() GPTracer _GPTracer__LINE__(__FILE__,__func__,__LINE__);
#define GP_TRACER_ENABLE(FILENAME) GPTracer::enable(FILENAME);
#define GP_TRACER_DISABLE GPTracer::disable();
#define GP_TRACE_VALUE(NAME, VALUE) GPTracer::traceQuantity(NAME, VALUE);
#else
#define GP_TRACE()
#define GP_TRACER_ENABLE(FILENAME)
#define GP_TRACER_DISABLE
#define GP_TRACE_VALUE()
#endif

#ifdef GP_TRACE_MEMORY
#define GP_TRACE_MEMORY_REPORT \
std::cout << "Total Memory Allocated : " << 0.000001 * __totalMemAllocated << " MB\n";\
std::cout << "Total Memory Deleted : " << 0.000001 * __totalMemDeleted << " MB\n";\
std::cout << "Total Memory Diff : " << 0.000001 * (__totalMemAllocated - __totalMemDeleted) << " MB\n";\

size_t __totalMemAllocated(0);
size_t __totalMemDeleted(0);
void *operator new(size_t size)
{
    // std::cout << "Allocating " << size << " Bytes.\n";
    __totalMemAllocated += size;
    return malloc(size);
}

void operator delete(void *memory, size_t size)
{
    // std::cout << "Deleting " << size << " Bytes.\n";
    __totalMemDeleted += size;
    free(memory);
}
#else
#define GP_TRACE_MEMORY_REPORT
#endif

//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>


class GPTracer
{
public:
    /**
     * @brief GPTracer constructor will check if the class "is enabled". If it is, it will record the creation time with respect to the
     * ZeroTime set during the last enable function call. It will also write that time to the output file and if needed, it will also print
     * it to terminal.
     * @param function Function name where the GPTracer object is created.
     * @param file File name where the GPTracer object is created.
     * @param num Line number where the GPTracer object is created.
     */
    GPTracer(const std::string& file, const std::string& function, int lineNumber);

    /**
     * GPTracer destructor will check if the class "is enabled". If it is, it will record the destruction time with respect to the
     * ZeroTime set during the last enable function call. It will also write that time to the output file and, if needed, it will also print
     * it to terminal.
     */
    ~GPTracer();

    /**
     * The enable function initializes an output file (output file stream ie std::ofstream) to write the events.
     * @param jsonFileName is the name of the output file to configure as the outuput file (it is in json format).
     */
    static void enable(const std::string& jsonFileName);

    /**
     * Overriden function for enable, but using the default filename.
     */
    static void enable();

    /**
     * @brief disable If the class "is enabled" (it's static variabable ms_bIsEnabled is true), the output file has a Footer written to it and the
     * output file stream is closed. Finally, the static member variable ms_bIsEnabled is set to false.
     */
    static void disable();

    /**
     * @brief Convenience overload of the method enable.
     * @param jsonFileName
     */
    static void start(const std::string& jsonFileName);

    /**
     * @brief Convenience overload of the method enable.
     */
    static void start();

    /**
     * @brief Convenience overload of the method disable.
     */
    static void stop();

    /**
     * @brief traceQuantity Allows to keep track of a specific variable in the output tracing file.
     * @param name Name of the variable to keep track of.
     * @param val Value of the variable to keep track of.
     */
    static void traceQuantity(const std::string& name, long val);

    /**
     * Getter function for the member variable that defines whether the output should be printed to terminal, or only to a file.
     * @return bool value.
     */
    bool printToTerminalIsSet();

    /**
     * Setter function for the member variable that defines whether the output should be printed to terminal, or only to a file.
     * @param s bool value to set the output to terminal control member variable.
     */
    void setPrintToTerminal(bool s);

private:
    /**
     * @brief writeHeader The outputfile needs a specific header to be compatible with Chrome Tracer app. This ads this header to
     * the output file.
     */
    static void writeHeader();

    /**
     * @brief writeFooter The outputfile needs a specific footer to be compatible with Chrome Tracer app. and close the arrays defined in
     * the json file.  This ads this footer (closing brackets) to the output file.
     */
    static void writeFooter();

    /**
     * @brief writeToFile This function writes a string to the output file.
     * @param str String to write.
     */
    static void writeToFile(const std::string& str);

    /**
     * @brief setZeroTime Sets the zero time, which is the time that will be considered zero in the tracer result. Typically, this is called
     * by the enable function.
     */
    static void setZeroTime();

    /**
     * @brief getTimeNow Wrapper function over chronos std library functionality to get the tick of this instant (in microseconds).
     * @return The actual time now in microseconds.
     */
    static long long getTimeNow();

    /**
     * @brief initialize Formats the fileName, FunctionName and line of code text shown in each event saved to the output file.
     * It then registers the threadId and the construction time for each instance of the class.
     */
    void initialize();

    /**
     * Removes extra back-slashes from the filename string.
     */
    void formatFileName();

    /**
     * removes  "__cdecl" from the function name.
     */
    void formatFunctionName();

    /**
     * Saves the construction time of this object. To later compute the time between construction and destruction of each object.
     */
    void registerConstructionTime();

    /**
     * Saves the destruction time of this object. See registerConstructionTime.
     */
    void registerFinalTime();

    /**
     * Stores a string, definiing a specific thread based on a hashing function. The same thread will always have the same stringId.
     */
    void registerThreadId();

    /**
     * Calculate duration between construction and destruction of an object.
     */
    void calculateDuration();

    /**
     * Print duration in miliseconds.
     */
    void printDurationMiliSec();

    /**
     * Write an event of type B (begin) in the output file.
     */
    void writeBeginEvent();

    /**
     * Write an event of type E (end) in the ouptut file.
     */
    void writeEndEvent();

    static bool ms_bIsEnabled;                  /**< Bool variable to store if the "class" (ie. the GPTracer) has been enabled. */
    static std::ofstream ms_OutputFileStream;   /**< Output file stream to write results. */
    static bool ms_bIsFirstEvent;               /**< Bool variable to check if this is the first event to be written to the file. */
    static std::mutex ms_outFileMutex;          /**< Mutex to guard the writing to file between threads. */
    static long long ms_iZeroTime;              /**< Integer value to store the origin-time (ie the Zero time) from which all other time measurements will depend. */

    bool m_bIsInitialized;          /**< Store if this object has been initialized properly. */
    bool m_bPrintToTerminal;        /**< Store if it is needed from this GPTracer object. to print to terminal too. */
    std::string m_sFileName;        /**< String to store the code file name where the GPTracer obj is instantiated. */
    std::string m_sFunctionName;    /**< String to store the function name. */
    int m_iLineNumber;              /**< The line number within the code file where the GPTracer obj is instantiated. */
    std::string m_iThreadId;        /**< A string identifier for the thread id in which the GPTracer obj is instantiated. */
    long long m_iBeginTime;         /**< The time when the tracer GPTracer obj is created. */
    long long m_iEndTime;           /**< The time when the tracer GPTracer obj is destructed. */
    double m_dDurationMilis;        /**< The time difference between GPTracer object creation and destruction in in milli seconds. */
}; // GPTracer

//=============================================================================================================
// DEFINE STATIC MEMBER VARIABLES
//=============================================================================================================

static const char* defaultTracerFileName("default_GPTracer_file.json");
bool GPTracer::ms_bIsEnabled(false);
std::ofstream GPTracer::ms_OutputFileStream;
bool GPTracer::ms_bIsFirstEvent(true);
std::mutex GPTracer::ms_outFileMutex;
long long GPTracer::ms_iZeroTime(0);

//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

GPTracer::GPTracer(const std::string &file, const std::string &function, int lineNumber)
: m_bIsInitialized(false)
, m_bPrintToTerminal(false)
, m_sFileName(file)
, m_sFunctionName(function)
, m_iLineNumber(lineNumber)
, m_iThreadId("0")
, m_iBeginTime(0)
, m_iEndTime(0)
, m_dDurationMilis(0.)
{
    if (ms_bIsEnabled)
    {
        initialize();
        writeBeginEvent();
    }
}

//=============================================================================================================

GPTracer::~GPTracer()
{
    if (ms_bIsEnabled && m_bIsInitialized)
    {
        registerFinalTime();
        writeEndEvent();
        if (m_bPrintToTerminal)
        {
            calculateDuration();
            printDurationMiliSec();
        }
    }
}

//=============================================================================================================

void GPTracer::enable(const std::string &jsonFileName)
{
    ms_OutputFileStream.open(jsonFileName);
    writeHeader();
    setZeroTime();
    if (ms_OutputFileStream.is_open())
    {
        ms_bIsEnabled = true;
    }
}

//=============================================================================================================

void GPTracer::enable()
{
    enable(defaultTracerFileName);
}

//=============================================================================================================

void GPTracer::disable()
{
    if (ms_bIsEnabled)
    {
        writeFooter();
        ms_OutputFileStream.flush();
        ms_OutputFileStream.close();
        ms_bIsEnabled = false;
    }
}

//=============================================================================================================

void GPTracer::start(const std::string &jsonFileName)
{
    enable(jsonFileName);
}

//=============================================================================================================

void GPTracer::start()
{
    enable();
}

//=============================================================================================================

void GPTracer::stop()
{
    disable();
}

//=============================================================================================================

void GPTracer::traceQuantity(const std::string &name, long val)
{
    long long timeNow = getTimeNow() - ms_iZeroTime;
    std::string s;
    s.append("{\"name\":\"").append(name).append("\",\"ph\":\"C\",\"ts\":");
    s.append(std::to_string(timeNow)).append(",\"pid\":1,\"tid\":1");
    s.append(",\"args\":{\"").append(name).append("\":").append(std::to_string(val)).append("}}\n");
    writeToFile(s);
}

//=============================================================================================================

void GPTracer::initialize()
{
    registerConstructionTime();
    registerThreadId();
    formatFileName();
    m_bIsInitialized = true;
}

//=============================================================================================================

void GPTracer::setZeroTime()
{
    ms_iZeroTime = getTimeNow();
}

//=============================================================================================================

void GPTracer::registerConstructionTime()
{
    m_iBeginTime = getTimeNow() - ms_iZeroTime;
}

//=============================================================================================================

void GPTracer::registerFinalTime()
{
    m_iEndTime = getTimeNow() - ms_iZeroTime;
}

//=============================================================================================================

long long GPTracer::getTimeNow()
{
    auto timeNow = std::chrono::high_resolution_clock::now();
    return std::chrono::time_point_cast<std::chrono::microseconds>(timeNow).time_since_epoch().count();
}

//=============================================================================================================

void GPTracer::registerThreadId()
{
    auto longId = std::hash<std::thread::id>{}(std::this_thread::get_id());
    m_iThreadId = std::to_string(longId).substr(0, 5);
}

//=============================================================================================================

void GPTracer::formatFunctionName()
{
    const char* pattern(" __cdecl");
    constexpr int patternLenght(8);
    size_t pos = m_sFunctionName.find(pattern);
    if (pos != std::string::npos) {
        m_sFunctionName.replace(pos, patternLenght, "");
    }
}

//=============================================================================================================

void GPTracer::formatFileName()
{
    const char* patternIn("\\");
    const char* patternOut("\\\\");
    constexpr int patternOutLength(4);
    size_t start_pos = 0;
    while ((start_pos = m_sFileName.find(patternIn, start_pos)) != std::string::npos)
    {
        m_sFileName.replace(start_pos, 1, patternOut);
        start_pos += patternOutLength;
    }
}

//=============================================================================================================

void GPTracer::calculateDuration()
{
    m_dDurationMilis = (m_iEndTime - m_iBeginTime) * 0.001;
}

//=============================================================================================================

void GPTracer::printDurationMiliSec()
{
    std::cout << "Scope: " << m_sFileName << " - " << m_sFunctionName << " DurationMs: " << m_dDurationMilis << "ms.\n";
}

//=============================================================================================================

void GPTracer::writeHeader()
{
    writeToFile("{\"displayTimeUnit\": \"ms\",\"traceEvents\":[\n");
}

//=============================================================================================================

void GPTracer::writeFooter()
{
    writeToFile("]}");
}

//=============================================================================================================

void GPTracer::writeToFile(const std::string& str)
{
    ms_outFileMutex.lock();
    if(ms_OutputFileStream.is_open()) {
        ms_OutputFileStream << str;
    }
    ms_outFileMutex.unlock();
}

//=============================================================================================================

void GPTracer::writeBeginEvent()
{
    std::string s;
    if (!ms_bIsFirstEvent)
        s.append(",");

    s.append("{\"name\":\"").append(m_sFunctionName).append("\",\"cat\":\"bst\",");
    s.append("\"ph\":\"B\",\"ts\":").append(std::to_string(m_iBeginTime)).append(",\"pid\":1,\"tid\":");
    s.append(m_iThreadId).append(",\"args\":{\"file path\":\"").append(m_sFileName).append("\",\"line number\":");
    s.append(std::to_string(m_iLineNumber)).append("}}\n");
    writeToFile(s);
    ms_bIsFirstEvent = false;
}

//=============================================================================================================

void GPTracer::writeEndEvent()
{
    std::string s;
    s.append(",{\"name\":\"").append(m_sFunctionName).append("\",\"cat\":\"bst\",");
    s.append("\"ph\":\"E\",\"ts\":").append(std::to_string(m_iEndTime)).append(",\"pid\":1,\"tid\":");
    s.append(m_iThreadId).append(",\"args\":{\"file path\":\"").append(m_sFileName).append("\",\"line number\":");
    s.append(std::to_string(m_iLineNumber)).append("}}\n");
    writeToFile(s);
}

//=============================================================================================================

bool GPTracer::printToTerminalIsSet()
{
    return m_bPrintToTerminal;
}

//=============================================================================================================

void GPTracer::setPrintToTerminal(bool s)
{
    m_bPrintToTerminal = s;
}


#endif //if TRACE defined
