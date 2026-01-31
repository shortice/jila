---@meta fio

--- @enum Jila_IO_Whence
Jila_IO_Whence = {
    SET = 0,
    CUR = 1,
    END = 2
}

--- @class Jila_IO
Jila_IO = {}

--- Writes data to the stream.
--- @param stream Jila_IO The stream to write to.
--- @param data string The string data to write.
--- @return number number The number of bytes written.
function Jila_IO_Write(stream, data) end

--- Reads data from the stream.
--- @param stream Jila_IO The stream to read from.
--- @param size number The number of bytes to read.
--- @return string string The data read.
function Jila_IO_Read(stream, size) end

--- Seeks to an offset in the stream.
--- @param stream Jila_IO The stream to seek in.
--- @param offset number The offset to seek to.
--- @param whence Jila_IO_Whence The reference point for the offset.
--- @return number The new position in the stream, or -1 on error.
--- 
--- @see Jila_GetError for read error.
function Jila_IO_Seek(stream, offset, whence) end

--- Gets the current position in the stream.
--- @param stream Jila_IO The stream.
--- @return number The current position, or -1 on error.
--- 
--- @see Jila_GetError for read error.
function Jila_IO_Tell(stream) end

--- Gets the size of the stream.
--- @param stream Jila_IO The stream.
--- @return number The size of the stream, or -1 on error.
--- 
--- @see Jila_GetError for read error.
function Jila_IO_GetSize(stream) end

--- Opens a file as an IO stream.
--- @param path string The path to the file.
--- @param mode string The mode to open the file in (e.g., "rb", "wb").
--- @return Jila_IO|nil Jila_IO The IO stream, or nil on error.
--- 
--- @see Jila_GetError for read error.
function Jila_IO_Open(path, mode) end
