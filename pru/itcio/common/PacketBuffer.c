#include "PacketBuffer.h"

struct PacketBuffer * PacketBufferFromPacketBufferStorage(unsigned char * pbs)
{
  return PacketBufferFromPacketBufferStorageInline(pbs);
}

void pbInit(struct PacketBuffer * pb, unsigned ringBufferBits)
{
  pbInitInline(pb,ringBufferBits);
}

unsigned int pbUsedBytes(struct PacketBuffer * pb)
{
  return pbUsedBytesInline(pb);
}

unsigned int pbAvailableBytes(struct PacketBuffer * pb)
{
  return pbAvailableBytesInline(pb);
}

void pbStartWritingPendingPacket(struct PacketBuffer * pb)
{
  pbStartWritingPendingPacketInline(pb);
}

unsigned int pbWriteByteInPendingPacket(struct PacketBuffer *pb, unsigned byteToStore)
{
  return pbWriteByteInPendingPacketInline(pb, byteToStore);
}

unsigned int pbCommitPendingPacket(struct PacketBuffer *pb)
{
  return pbCommitPendingPacketInline(pb);
}

unsigned int pbGetLengthOfOldestPacket(struct PacketBuffer * pb)
{
  return pbGetLengthOfOldestPacketInline(pb);
}

int pbGetTypeOfOldestPacketIfAny(struct PacketBuffer * pb)
{
  return pbGetTypeOfOldestPacketIfAnyInline(pb);
}

unsigned int pbStartReadingOldestPacket(struct PacketBuffer * pb)
{
  return pbStartReadingOldestPacketInline(pb);
}

int pbReadByteFromOldestPacket(struct PacketBuffer *pb)
{
  return pbReadByteFromOldestPacketInline(pb);
}

unsigned int pbDropOldestPacket(struct PacketBuffer *pb)
{
  return pbDropOldestPacketInline(pb);
}

int pbWritePacketIfPossible(struct PacketBuffer *pb, unsigned char * data, unsigned length)
{
  if (!pb || !data || length == 0) return -PBE_INVAL;
  if (length > 255) return -PBE_FBIG;
  if (pbAvailableBytes(pb) < length + 1) return -PBE_NOMEM;
  pbStartWritingPendingPacket(pb);
  /*XXX LET'S GET SOME MEMCPY ACTION MOVING IN HERE*/
  while (length-- > 0) pbWriteByteInPendingPacketInline(pb, *data++);
  pbCommitPendingPacket(pb);
  return 0;
}

int pbReadPacketIfPossible(struct PacketBuffer *pb, unsigned char * data, unsigned length)
{
  unsigned plen, i;
  if (!pb || !data || length == 0) return -PBE_INVAL;
  plen = pbGetLengthOfOldestPacket(pb);
  if (plen == 0) return 0;
  if (plen > length) return -PBE_FBIG;
  pbStartReadingOldestPacket(pb);
  /*XXX LET'S GET SOME MEMCPY ACTION MOVING IN HERE*/
  for (i = 0; i < plen; ++i)
    data[i] = pbReadByteFromOldestPacketInline(pb);
  pbDropOldestPacket(pb);
  return plen;
}

#ifdef __KERNEL__
#include <asm/uaccess.h>           /* Required for the copy to user function */
int pbWritePacketIfPossibleFromUser(struct PacketBuffer *pb, void __user * from, unsigned length)
{
  u8 byte;
  u8 __user * cfrom = (u8*) from;
  unsigned i;
  if (!pb || !from || length == 0) return -PBE_INVAL;
  if (length > 255) return -PBE_FBIG;
  if (pbAvailableBytes(pb) < length + 1) return -PBE_NOMEM;
  pbStartWritingPendingPacket(pb);

  /*XXX LET'S GET SOME MEMCPYISH ACTION MOVING IN HERE*/
  for (i = 0; i < length; ++i) {
    int ret = copy_from_user(&byte, &cfrom[i], 1);
    if (ret != 0) {
      printk(KERN_ERR "pb: copy_from_user failed\n");
      return -PBE_FAULT;
    }
    pbWriteByteInPendingPacketInline(pb, byte);
  }
  pbCommitPendingPacket(pb);
  return 0;
}

int pbReadPacketIfPossibleToUser(struct PacketBuffer *pb, void __user * to, unsigned length)
{
  unsigned plen, i;
  int error = 0;
  u8 __user * cto = (u8*) to;
  if (!pb || !to || length == 0) return -PBE_INVAL;
  plen = pbGetLengthOfOldestPacket(pb);
  if (plen == 0) return 0;
  if (plen > length) return -PBE_FBIG;
  pbStartReadingOldestPacket(pb);
  /*XXX LET'S GET SOME MEMCPY ACTION MOVING IN HERE*/
  for (i = 0; i < plen; ++i) {
    u8 byte = (u8) pbReadByteFromOldestPacketInline(pb);
    error = copy_to_user(&cto[i], &byte, 1);
    if (error < 0)
      break;
  }

  pbDropOldestPacket(pb);
  if (error < 0) return error;
  return plen;
}
#endif

int pbTransferPacketIfPossible(struct PacketBuffer *pbto, struct PacketBuffer *pbfrom)
{
  unsigned tlen;
  if (!pbto || !pbfrom) return -PBE_INVAL;
  tlen = pbGetLengthOfOldestPacket(pbfrom);
  if (tlen == 0) return -PBE_AGAIN;
  if (pbAvailableBytes(pbto) < tlen + 1) return -PBE_NOMEM;
  pbStartReadingOldestPacket(pbfrom);
  pbStartWritingPendingPacket(pbto);
  while (tlen-- > 0)
    pbWriteByteInPendingPacketInline(pbto,
                                     pbReadByteFromOldestPacketInline(pbfrom));
  pbCommitPendingPacket(pbto);
  pbDropOldestPacket(pbfrom);
  return 0;
}


#ifdef __KERNEL__
#include <linux/module.h>
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Dave Ackley <ackley@ackleyshack.com>");
MODULE_DESCRIPTION("T2 intertile packet buffers");
#endif
