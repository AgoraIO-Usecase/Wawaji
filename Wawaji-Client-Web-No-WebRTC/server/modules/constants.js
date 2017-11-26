const WawajiStatus = {
    INITIAL: 0,
    INITIALIZING: 1,
    WAITING: 2,
    READY: 3,
    BUSY: 4,
    RESULT: 6
};

const StreamMethod = {
    IMAGES: 0,
    JSMPEG: 1
}

module.exports =  {
    WawajiStatus: WawajiStatus,
    StreamMethod: StreamMethod
}