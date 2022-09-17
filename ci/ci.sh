# go to build directory
cd ../build

# Build and check for success
make clean
make OS_CMDS=POSIX
MAKE_RESULT=$?
if [ $MAKE_RESULT != 0 ]; then
    echo "Build failed"
    
    exit $MAKE_RESULT
fi

echo "Build succeeded"

# Run the test script and check for success
timeout 1m ./numstr_test.exe
TEST_RESULT=$?
if [ $TEST_RESULT != 0 ]; then
    echo "Test failed"
else
    echo "Tests passed"
fi

exit $TEST_RESULT