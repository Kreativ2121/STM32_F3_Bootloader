using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bootloader
{
    internal class MDataPacket
    {
        public byte[] mData;
        public UInt32 mAddr;
        public int mLineNr = -1;

        public MDataPacket(UInt32 addr, byte[] data, int lineNr = 0)
        {
            mAddr = addr;
            mData = data;
            mLineNr = lineNr;
        }

        public string genStr()
        {
            int cnt2 = mData.Length;
            string str = ":";
            str += cnt2.ToString("X2");
            int addr = (int)(mAddr & 0xFFFF);
            str += addr.ToString("X4");
            str += "00";
            for (int i = 0; i < mData.Length; i++)
                str += mData[i].ToString("X2");

            int crcSum = 0;
            crcSum += cnt2;
            crcSum += addr >> 8;
            crcSum += addr >> 0;
            for (int i = 0; i < cnt2 ; i++) crcSum += mData[i];
            crcSum = (0x100 - (byte)crcSum);
            crcSum &= 0xFF;
            // :10 00 00 00 B8 0B 00 20 35 A8 00 08 3D A6 00 08 3F A6 00 08 50
            str += crcSum.ToString( "X2" );

            return str;
        }

        public static bool operator == (MDataPacket a, MDataPacket b)
        {
            if (a.mAddr == b.mAddr)
            {
                if (a.mData.Length == b.mData.Length)
                {
                    for (int i = 0; i < a.mData.Length; i++)
                    {
                        if (a.mData[i] != b.mData[i])
                        {
                            return false;
                        }
                    }

                    return true;
                }
            }

            return false;
        }

        public static bool operator != (MDataPacket a, MDataPacket b)
        {
            return !(a == b);
        }
    }
}
