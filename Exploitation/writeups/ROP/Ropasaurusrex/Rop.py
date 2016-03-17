import struct

class RopChain:

    __doc__=\
    '''

    RopChain is a class that was designed to make life easier while creating ROP exploits.


    There are two ways to create a rop chain:

        1) Add the pop_pop_ret addresses before creating the chain.

            ropChain.addPopRet(3,cleanup_addr)
            ropChain.addLink(func_addr,[p1,p2,p3])


        2) explicitaly add the address of each cleanup for each link. For exlample

            ropCHain.addLink(func_addr, [p1,p2,..,pn], pppr)

    When you are ready to create your payload, you can get the full rop chain with

    ropChain.getChain()

    '''


    chain = ""
    popRet = {}

    def addPopRet(self,numPops,addr):
        RopChain.popRet[numPops] = addr

    @classmethod
    def getCleanup(self,key):
        #if the key is in the hash table
        if RopChain.popRet.has_key(key):
        #return the value
            return RopChain.popRet[key]
        #otherwise, return junk
        else:
            return 0xdeadbeef

    def addLink(self, addr, args = None, cleanup = None):

        if cleanup is None:
        #if the function takes multiple args
            if type(args) is list:
        #get the proper cleanup address from the table and add it to the chain along with the address
                RopChain.chain += struct.pack('<II',addr,RopChain.getCleanup(len(args)))
        #add each arg to the chain
                for i in range(0,len(args)):
                    RopChain.chain += struct.pack('<I',args[i])
        #if the function takes only one argument
            elif type(args) is int:
                RopChain.chain+=struct.pack('<III',addr,RopChain.getCleanup(1),args)
        #if the function takes no args
            elif args is None:
                RopChain.chain+=struct.pack('<II',addr,RopChain.getChain(0))

        else:
            RopChain.chain += struct.pack('<II',addr,cleanup)

            if type(args) is list:
                for i in range(0,len(args)):
                    RopChain.chain += struct.pack('<I',args[i])
            elif type(args) is int:
                RopChain.chain+=struct.pack('<I',args)

    def getChain(self):
        return RopChain.chain



