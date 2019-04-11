/*
    lua_openscript_cl "module networking test.lua";
*/

net.Receive("Test send", function(len)
    if(!len)then
        print("no data");
        return;
    end
    local str   = net.ReadString() or "failed";
    local vec   = net.ReadVector() or Vector(0,0,0);
    local fl    = net.ReadFloat() or 0.0001;

    print(string.format("Values: \nstr: %s\nvec: %s\nfl: %f", str,tostring(vec),fl));
end)

net.Start("Test Receive");
    net.WriteString("Test Net Message");
net.SendToServer();

/*
    results you should be expecting.

    net.Receive("Test send"); 
    [
        in-game console output:

        Values: 
        str: Test Net Message
        vec: 1002.000000 2001.000000 3000.000000
        fl: 0.133700
    ]

    net.Start("Test Receive");
    [
        Console output:

        out: (pointer to player edict) Test Net Message
    ]
*/
