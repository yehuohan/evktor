--- @param ver(string)
function set_xmakever(ver) end

--- @param name(string) The target name
--- @param fn(function)
function target(name, fn) end

--- @param kind(string)
function set_kind(kind) end

--- @param files(string)
function add_files(files) end

--- xmake require --info <dep-name>
--- @param dep string
--- @param opts table|nil
function add_requires(dep, opts) end
