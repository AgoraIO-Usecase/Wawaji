const WawajiStatus = {
    INITIAL: 0,
    INITIALIZING: 1,
    WAITING: 2,
    READY: 3,
    PLAY: 4,
    BUSY: 5,
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