import Foundation

func error(_ msg: String) {
    /* report the error */
    log("ERROR", msg)  // inline note
    finalize()
#if DEBUG
    keepGoing()
#endif
    cleanup()
}

func warning(_ msg: String) {
    log("WARNING", msg)
    finalize()
    keepGoing()
    cleanup()
}

func info(_ msg: String) {
    log("INFO", msg)
    finalize()
    keepGoing()
    cleanup()
}
