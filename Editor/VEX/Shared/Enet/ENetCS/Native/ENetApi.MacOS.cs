#region License
/*
ENet for C#
Copyright (c) 2013 James F. Bellinger <jfb@zer7.com>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#endregion

#pragma warning disable 1591

using System;
using System.Runtime.InteropServices;

namespace ENet.Native
{
    unsafe sealed class ENetApiMacOS : ENetApi
    {
        const string LIB = "libenet.dylib";

        #region Address Functions
        public override int address_set_host(ref ENetAddress address, byte* hostName)
        {
            return native_address_set_host(ref address, hostName);
        }

        public override int address_set_host(ref ENetAddress address, byte[] hostName)
        {
            return native_address_set_host(ref address, hostName);
        }

        public override int address_get_host(ref ENetAddress address, byte* hostName, IntPtr nameLength)
        {
            return native_address_get_host(ref address, hostName, nameLength);
        }

        public override int address_get_host(ref ENetAddress address, byte[] hostName, IntPtr nameLength)
        {
            return native_address_get_host(ref address, hostName, nameLength);
        }

        public override int address_get_host_ip(ref ENetAddress address, byte* hostIP, IntPtr ipLength)
        {
            return native_address_get_host_ip(ref address, hostIP, ipLength);
        }

        public override int address_get_host_ip(ref ENetAddress address, byte[] hostIP, IntPtr ipLength)
        {
            return native_address_get_host_ip(ref address, hostIP, ipLength);
        }

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_address_set_host")]
        static extern int native_address_set_host(ref ENetAddress address, byte* hostName);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_address_set_host")]
        static extern int native_address_set_host(ref ENetAddress address, byte[] hostName);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_address_get_host")]
        static extern int native_address_get_host(ref ENetAddress address, byte* hostName, IntPtr nameLength);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_address_get_host")]
        static extern int native_address_get_host(ref ENetAddress address, byte[] hostName, IntPtr nameLength);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_address_get_host_ip")]
        static extern int native_address_get_host_ip(ref ENetAddress address, byte* hostIP, IntPtr ipLength);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_address_get_host_ip")]
        static extern int native_address_get_host_ip(ref ENetAddress address, byte[] hostIP, IntPtr ipLength);
        #endregion

        #region Global Functions
        public override int initialize_with_callbacks(uint version, ref ENetCallbacks inits)
        {
            return native_initialize_with_callbacks(version, ref inits);
        }

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_initialize_with_callbacks")]
        static extern int native_initialize_with_callbacks(uint version, ref ENetCallbacks inits);
        #endregion

        #region Host Functions
        public override void host_bandwidth_limit(ENetHost* host, uint incomingBandwidth, uint outgoingBandwidth)
        {
            native_host_bandwidth_limit(host, incomingBandwidth, outgoingBandwidth);
        }

        public override void host_broadcast(ENetHost* host, byte channelID, ENetPacket* packet)
        {
            native_host_broadcast(host, channelID, packet);
        }

        public override void host_channel_limit(ENetHost* host, IntPtr channelLimit)
        {
            native_host_channel_limit(host, channelLimit);
        }

        public override int host_check_events(ENetHost* host, out ENetEvent @event)
        {
            return native_host_check_events(host, out @event);
        }

        public override void host_compress(ENetHost* host, ENetCompressor* compressor)
        {
            native_host_compress(host, compressor);
        }

        public override int host_compress_with_range_encoder(ENetHost* host)
        {
            return native_host_compress_with_range_encoder(host);
        }

        public override ENetPeer* host_connect(ENetHost* host, ref ENetAddress address, IntPtr channelCount, uint data)
        {
            return native_host_connect(host, ref address, channelCount, data);
        }

        public override ENetHost* host_create(ENetAddress* address,
            IntPtr peerLimit, IntPtr channelLimit, uint incomingBandwidth, uint outgoingBandwidth)
        {
            return native_host_create(address, peerLimit, channelLimit, incomingBandwidth, outgoingBandwidth);
        }

        public override ENetHost* host_create(ref ENetAddress address,
            IntPtr peerLimit, IntPtr channelLimit, uint incomingBandwidth, uint outgoingBandwidth)
        {
            return native_host_create(ref address, peerLimit, channelLimit, incomingBandwidth, outgoingBandwidth);
        }

        public override void host_destroy(ENetHost* host)
        {
            native_host_destroy(host);
        }

        public override void host_flush(ENetHost* host)
        {
            native_host_flush(host);
        }

        public override int host_service(ENetHost* host, ENetEvent* @event, uint timeout)
        {
            return native_host_service(host, @event, timeout);
        }

        public override int host_service(ENetHost* host, out ENetEvent @event, uint timeout)
        {
            return native_host_service(host, out @event, timeout);
        }

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_bandwidth_limit")]
        static extern void native_host_bandwidth_limit(ENetHost* host, uint incomingBandwidth, uint outgoingBandwidth);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_broadcast")]
        static extern void native_host_broadcast(ENetHost* host, byte channelID, ENetPacket* packet);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_channel_limit")]
        static extern void native_host_channel_limit(ENetHost* host, IntPtr channelLimit);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_check_events")]
        static extern int native_host_check_events(ENetHost* host, out ENetEvent @event);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_compress")]
        static extern void native_host_compress(ENetHost* host, ENetCompressor* compressor);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_compress_with_range_encoder")]
        static extern int native_host_compress_with_range_encoder(ENetHost* host);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_connect")]
        static extern ENetPeer* native_host_connect(ENetHost* host, ref ENetAddress address, IntPtr channelCount, uint data);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_create")]
        static extern ENetHost* native_host_create(ENetAddress* address,
            IntPtr peerLimit, IntPtr channelLimit, uint incomingBandwidth, uint outgoingBandwidth);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_create")]
        static extern ENetHost* native_host_create(ref ENetAddress address,
            IntPtr peerLimit, IntPtr channelLimit, uint incomingBandwidth, uint outgoingBandwidth);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_destroy")]
        static extern void native_host_destroy(ENetHost* host);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_flush")]
        static extern void native_host_flush(ENetHost* host);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_service")]
        static extern int native_host_service(ENetHost* host, ENetEvent* @event, uint timeout);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_host_service")]
        static extern int native_host_service(ENetHost* host, out ENetEvent @event, uint timeout);
        #endregion

        #region Miscellaneous Functions
        public override uint time_get()
        {
            return native_time_get();
        }

        public override void time_set(uint newTimeBase)
        {
            native_time_set(newTimeBase);
        }

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_time_get")]
        static extern uint native_time_get();

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_time_set")]
        static extern void native_time_set(uint newTimeBase);
        #endregion

        #region Packet Functions
        public override ENetPacket* packet_create(IntPtr data, IntPtr dataLength, PacketFlags flags)
        {
            return native_packet_create(data, dataLength, flags);
        }

        public override void packet_destroy(ENetPacket* packet)
        {
            native_packet_destroy(packet);
        }

        public override int packet_resize(ENetPacket* packet, IntPtr dataLength)
        {
            return native_packet_resize(packet, dataLength);
        }

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_packet_create")]
        static extern ENetPacket* native_packet_create(IntPtr data, IntPtr dataLength, PacketFlags flags);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_packet_destroy")]
        static extern void native_packet_destroy(ENetPacket* packet);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_packet_resize")]
        static extern int native_packet_resize(ENetPacket* packet, IntPtr dataLength);
        #endregion

        #region Peer Functions
        public override void peer_disconnect(ENetPeer* peer, uint data)
        {
            native_peer_disconnect(peer, data);
        }

        public override void peer_disconnect_now(ENetPeer* peer, uint data)
        {
            native_peer_disconnect_now(peer, data);
        }

        public override void peer_disconnect_later(ENetPeer* peer, uint data)
        {
            native_peer_disconnect_later(peer, data);
        }

        public override void peer_ping(ENetPeer* peer)
        {
            native_peer_ping(peer);
        }

        public override void peer_ping_interval(ENetPeer* peer, uint pingInterval)
        {
            native_peer_ping_interval(peer, pingInterval);
        }

        public override ENetPacket* peer_receive(ENetPeer* peer, out byte channelID)
        {
            return native_peer_receive(peer, out channelID);
        }

        public override void peer_reset(ENetPeer* peer)
        {
            native_peer_reset(peer);
        }

        public override int peer_send(ENetPeer* peer, byte channelID, ENetPacket* packet)
        {
            return native_peer_send(peer, channelID, packet);
        }

        public override void peer_throttle_configure(ENetPeer* peer, uint interval, uint acceleration, uint deceleration)
        {
            native_peer_throttle_configure(peer, interval, acceleration, deceleration);
        }

        public override void peer_timeout(ENetPeer* peer, uint timeoutLimit, uint timeoutMinimum, uint timeoutMaximum)
        {
            native_peer_timeout(peer, timeoutLimit, timeoutMinimum, timeoutMaximum);
        }

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_peer_disconnect")]
        static extern void native_peer_disconnect(ENetPeer* peer, uint data);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_peer_disconnect_now")]
        static extern void native_peer_disconnect_now(ENetPeer* peer, uint data);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_peer_disconnect_later")]
        static extern void native_peer_disconnect_later(ENetPeer* peer, uint data);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_peer_ping")]
        static extern void native_peer_ping(ENetPeer* peer);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_peer_ping_interval")]
        static extern void native_peer_ping_interval(ENetPeer* peer, uint pingInterval);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_peer_receive")]
        static extern ENetPacket* native_peer_receive(ENetPeer* peer, out byte channelID);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_peer_reset")]
        static extern void native_peer_reset(ENetPeer* peer);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_peer_send")]
        static extern int native_peer_send(ENetPeer* peer, byte channelID, ENetPacket* packet);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_peer_throttle_configure")]
        static extern void native_peer_throttle_configure(ENetPeer* peer, uint interval, uint acceleration, uint deceleration);

        [DllImport(LIB, CallingConvention = CallingConvention.Cdecl, EntryPoint = "enet_peer_timeout")]
        static extern void native_peer_timeout(ENetPeer* peer, uint timeoutLimit, uint timeoutMinimum, uint timeoutMaximum);
        #endregion
    }
}
