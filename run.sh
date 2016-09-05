
USAGE=(
    "USAGE: run.sh (start | stop | report <SomeQuery> | help)",
    "       start  - will start server for collecting data",
    "       stop   - will stop server",
    "       report - will print the result of query processing to the current terminal session",
    "       help   - will print valid cmd list",
)

if [ "$1" = "-h" -o "$1" = "help" ]; then
    printf '%s\n' "${USAGE[@]}"
    exit
fi

./bin/simpleTimeTrackerEXE $@
