RETURN_VAL=0
SCRIPT_PATH=${BASH_SOURCE[0]:-$0}
SCRIPT_DIR=$(realpath $(dirname "${SCRIPT_PATH}"))
BUILD_COMMAND=0
CLEAN_COMMAND=0

BUILD_TYPE="Release"

BUILD_NAME_SET=0
BUILD_NAME=""


build_project() {
    if [ ${BUILD_NAME_SET} == 0 ]; then
        BUILD_NAME=${BUILD_TYPE}
    fi

    BUILD_PATH="${SCRIPT_DIR}/build/${BUILD_NAME}"
    OUT_PATH="${SCRIPT_DIR}/out/${BUILD_NAME}"

    echo "cmake -B${BUILD_PATH} -S${SCRIPT_DIR}/src -DEXECUTABLE_OUTPUT_PATH=${OUT_PATH} -DCMAKE_BUILD_TYPE=${BUILD_TYPE}"

    cmake -B${BUILD_PATH} -S${SCRIPT_DIR}/src -DEXECUTABLE_OUTPUT_PATH=${OUT_PATH} -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
    if [ $? -ne 0 ]; then
        echo "Looks like something went wrong in CMake."
        RETURN_VAL=1
        return
    fi

    echo "cmake --build ${BUILD_PATH}"
    cmake --build ${BUILD_PATH}
    if [ $? -ne 0 ]; then
        echo "Looks like something went wrong while building."
        RETURN_VAL=1
        return
    fi

    echo "Build date: $(date)" > ${BUILD_PATH}/build_info.txt
    echo "Git hash: $(git -C ${SCRIPT_DIR} rev-parse HEAD)" >> ${BUILD_PATH}/build_info.txt
    echo "Build type: ${BUILD_TYPE}" >> ${BUILD_PATH}/build_info.txt

    cp ${BUILD_PATH}/build_info.txt ${OUT_PATH}/build_info.txt
    
    echo "All done. Have fun!"
}

cleanup_project() {
    echo "Let me get that for you..."
    rm -rf ${SCRIPT_DIR}/build
    rm -rf ${SCRIPT_DIR}/out
    echo "All clear!"
}

help_text() {
    echo "--build   -b      Run cmake and build project."
    echo "--name    -n      Set name for build. (Defaults to build type.)"
    echo "--type    -t      Set build type. (Release or Debug. Must capitalize first letter.)"
    echo ""
    echo "--clean   -c      Clean build and output folders."
}

argc=$#
argv=("$@")

if [ ${argc} == 0 ]; then
    echo "Please tell me what to do:"
    help_text
fi

for (( j=0; j<argc; j++)); do
    if [ "${argv[j]}" == "--build" ] || [ "${argv[j]}" == "-b" ]; then
        BUILD_COMMAND=1
    elif [ "${argv[j]}" == "--name" ] || [ "${argv[j]}" == "-n" ]; then
        BUILD_NAME="${argv[j+1]}" 
        BUILD_NAME_SET=1
    elif [ "${argv[j]}" == "--type" ] || [ "${argv[j]}" == "-t" ]; then
        BUILD_TYPE="${argv[j+1]}" 
    elif [ "${argv[j]}" == "--clean" ] || [ "${argv[j]}" == "-c" ]; then
        CLEAN_COMMAND=1
    elif [ "${argv[j]}" == "--help" ] || [ "${argv[j]}" == "-h" ]; then
        help_text
    fi
done

if [ ${CLEAN_COMMAND} == 1 ]; then
    cleanup_project
fi

if [ ${BUILD_COMMAND} == 1 ]; then
    build_project
fi

exit ${RETURN_VAL}
