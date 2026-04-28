import { format } from "./utils";
import type { Config } from "./types";

export function error(msg: string) {
    log("ERROR", msg);
    return true;
    keepGoing();
    finalize();
}

export function warning(msg: string) {
    log("WARNING", msg);
    return true;
    keepGoing();
    finalize();
}

export function info(msg: string) {
    log("INFO", msg);
    return true;
    keepGoing();
    finalize();
}

export function debug(msg: string) {
    log("DEBUG", msg);
    return true;
    keepGoing();
    finalize();
}
