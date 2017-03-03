#region License
/*
ENet for C#
Copyright (c) 2011-2013 James F. Bellinger <jfb@zer7.com>

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

namespace ENet.Native
{
    public unsafe abstract class ENetApi
    {
        public const uint ENET_HOST_ANY = 0;
        public const uint ENET_HOST_BROADCAST = 0xffffffff;
        public const uint ENET_PEER_PACKET_THROTTLE_SCALE = 32;
        public const uint ENET_PEER_PACKET_THROTTLE_ACCELERATION = 2;
        public const uint ENET_PEER_PACKET_THROTTLE_DECELERATION = 2;
        public const uint ENET_PEER_PACKET_THROTTLE_INTERVAL = 5000;
        public const uint ENET_PEER_PING_INTERVAL = 500;
        public const uint ENET_PEER_TIMEOUT_LIMIT = 32;
        public const uint ENET_PEER_TIMEOUT_MINIMUM = 5000;
        public const uint ENET_PEER_TIMEOUT_MAXIMUM = 30000;
        public const uint ENET_PROTOCOL_MINIMUM_CHANNEL_COUNT = 0x01;
        public const uint ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT = 0xff;
        public const uint ENET_PROTOCOL_MAXIMUM_FRAGMENT_COUNT = 1024 * 1024;
        public const uint ENET_PROTOCOL_MAXIMUM_PACKET_SIZE = 1024 * 1024 * 1024;
        public const uint ENET_PROTOCOL_MAXIMUM_PEER_ID = 0xfff;
        const uint ENET_VERSION = (1 << 16) | (3 << 8) | (6 << 0);

        #region Platform Detection
        internal static ENetApi _platform;
        internal static object _platformLock = new object();

        internal ENetApi()
        {

        }

        internal static ENetApi Platform
        {
            get
            {
                if (_platform == null)
                {
                    lock (_platformLock)
                    {
                        if (_platform == null)
                        {
                            foreach (ENetApi platform in new ENetApi[]
                                {
                                    new ENetApiX64(),
                                    new ENetApiX86(),
                                    new ENetApiLinux(),
                                    new ENetApiMacOS()
                                })
                            {
                                try
                                {
                                    ENetCallbacks inits = new ENetCallbacks();
                                    if (platform.initialize_with_callbacks(ENET_VERSION, ref inits) >= 0)
                                    {
                                        _platform = platform; return platform;
                                    }
                                }
                                catch (BadImageFormatException)
                                {
                                    continue;
                                }
                                catch (DllNotFoundException)
                                {
                                    continue;
                                }
                                catch (EntryPointNotFoundException)
                                {
                                    continue;
                                }
                            }

                            throw new ENetException
                                ("The ENet native library failed to initialize." +
                                    " Make sure ENetX86.dll and ENetX64.dll are in the program directory, and that" +
                                    " you are running on a x86 or x64-based computer." +
                                    " If you are running on Linux, make sure the libenet.so.1 is in your path." +
                                    " On Ubuntu Linux, install the libenet1a package (1.3.3 or newer) if you haven't already." +
                                    " If you are running on MacOS, make sure libenet.dylib is in your path or program directory.");
                        }

                        return _platform;
                    }
                }

                return _platform;
            }
        }
        #endregion

        #region Address Functions
        public static int enet_address_set_host(ref ENetAddress address, byte* hostName)
        {
            return Platform.address_set_host(ref address, hostName);
        }

        public static int enet_address_set_host(ref ENetAddress address, byte[] hostName)
        {
            return Platform.address_set_host(ref address, hostName);
        }

        public static int enet_address_get_host(ref ENetAddress address, byte* hostName, IntPtr nameLength)
        {
            return Platform.address_get_host(ref address, hostName, nameLength);
        }

        public static int enet_address_get_host(ref ENetAddress address, byte[] hostName, IntPtr nameLength)
        {
            return Platform.address_get_host(ref address, hostName, nameLength);
        }

        public static int enet_address_get_host_ip(ref ENetAddress address, byte* hostIP, IntPtr ipLength)
        {
            return Platform.address_get_host_ip(ref address, hostIP, ipLength);
        }

        public static int enet_address_get_host_ip(ref ENetAddress address, byte[] hostIP, IntPtr ipLength)
        {
            return Platform.address_get_host_ip(ref address, hostIP, ipLength);
        }

        public abstract int address_set_host(ref ENetAddress address, byte* hostName);

        public abstract int address_set_host(ref ENetAddress address, byte[] hostName);

        public abstract int address_get_host(ref ENetAddress address, byte* hostName, IntPtr nameLength);

        public abstract int address_get_host(ref ENetAddress address, byte[] hostName, IntPtr nameLength);

        public abstract int address_get_host_ip(ref ENetAddress address, byte* hostIP, IntPtr ipLength);

        public abstract int address_get_host_ip(ref ENetAddress address, byte[] hostIP, IntPtr ipLength);
        #endregion

        #region Global Functions
        public abstract int initialize_with_callbacks(uint version, ref ENetCallbacks inits);
        #endregion

        #region Host Functions
        public static void enet_host_bandwidth_limit(ENetHost* host, uint incomingBandwidth, uint outgoingBandwidth)
        {
            Platform.host_bandwidth_limit(host, incomingBandwidth, outgoingBandwidth);
        }

        public static void enet_host_broadcast(ENetHost* host, byte channelID, ENetPacket* packet)
        {
            Platform.host_broadcast(host, channelID, packet);
        }

        public static void enet_host_channel_limit(ENetHost* host, IntPtr channelLimit)
        {
            Platform.host_channel_limit(host, channelLimit);
        }

        public static int enet_host_check_events(ENetHost* host, out ENetEvent @event)
        {
            return Platform.host_check_events(host, out @event);
        }

        public static ENetPeer* enet_host_connect(ENetHost* host, ref ENetAddress address, IntPtr channelCount, uint data)
        {
            return Platform.host_connect(host, ref address, channelCount, data);
        }

        public static void enet_host_compress(ENetHost* host, ENetCompressor* compressor)
        {
            Platform.host_compress(host, compressor);
        }

        public static int enet_host_compress_with_range_encoder(ENetHost* host)
        {
            return Platform.host_compress_with_range_encoder(host);
        }

        public static ENetHost* enet_host_create(ENetAddress* address,
            IntPtr peerLimit, IntPtr channelLimit, uint incomingBandwidth, uint outgoingBandwidth)
        {
            return Platform.host_create(address, peerLimit, channelLimit, incomingBandwidth, outgoingBandwidth);
        }

        public static ENetHost* enet_host_create(ref ENetAddress address,
            IntPtr peerLimit, IntPtr channelLimit, uint incomingBandwidth, uint outgoingBandwidth)
        {
            return Platform.host_create(ref address, peerLimit, channelLimit, incomingBandwidth, outgoingBandwidth);
        }

        public static void enet_host_destroy(ENetHost* host)
        {
            Platform.host_destroy(host);
        }

        public static void enet_host_flush(ENetHost* host)
        {
            Platform.host_flush(host);
        }

        public static int enet_host_service(ENetHost* host, ENetEvent* @event, uint timeout)
        {
            return Platform.host_service(host, @event, timeout);
        }

        public static int enet_host_service(ENetHost* host, out ENetEvent @event, uint timeout)
        {
            return Platform.host_service(host, out @event, timeout);
        }

        public abstract void host_bandwidth_limit(ENetHost* host, uint incomingBandwidth, uint outgoingBandwidth);

        public abstract void host_broadcast(ENetHost* host, byte channelID, ENetPacket* packet);

        public abstract void host_channel_limit(ENetHost* host, IntPtr channelLimit);

        public abstract int host_check_events(ENetHost* host, out ENetEvent @event);

        public abstract ENetPeer* host_connect(ENetHost* host, ref ENetAddress address, IntPtr channelCount, uint data);

        public abstract void host_compress(ENetHost* host, ENetCompressor* compressor);

        public abstract int host_compress_with_range_encoder(ENetHost* host);

        public abstract ENetHost* host_create(ENetAddress* address,
            IntPtr peerLimit, IntPtr channelLimit, uint incomingBandwidth, uint outgoingBandwidth);

        public abstract ENetHost* host_create(ref ENetAddress address,
            IntPtr peerLimit, IntPtr channelLimit, uint incomingBandwidth, uint outgoingBandwidth);

        public abstract void host_destroy(ENetHost* host);

        public abstract void host_flush(ENetHost* host);

        public abstract int host_service(ENetHost* host, ENetEvent* @event, uint timeout);

        public abstract int host_service(ENetHost* host, out ENetEvent @event, uint timeout);
        #endregion

        #region Miscellaneous Functions
        public static uint enet_time_get()
        {
            return Platform.time_get();
        }

        public static void enet_time_set(uint newTimeBase)
        {
            Platform.time_set(newTimeBase);
        }

        public abstract uint time_get();

        public abstract void time_set(uint newTimeBase);
        #endregion

        #region Packet Functions
        public static ENetPacket* enet_packet_create(IntPtr data, IntPtr dataLength, PacketFlags flags)
        {
            return Platform.packet_create(data, dataLength, flags);
        }

        public static void enet_packet_destroy(ENetPacket* packet)
        {
            Platform.packet_destroy(packet);
        }

        public static int enet_packet_resize(ENetPacket* packet, IntPtr dataLength)
        {
            return Platform.packet_resize(packet, dataLength);
        }

        public abstract ENetPacket* packet_create(IntPtr data, IntPtr dataLength, PacketFlags flags);

        public abstract void packet_destroy(ENetPacket* packet);

        public abstract int packet_resize(ENetPacket* packet, IntPtr dataLength);
        #endregion

        #region Peer Functions
        public static void enet_peer_disconnect(ENetPeer* peer, uint data)
        {
            Platform.peer_disconnect(peer, data);
        }

        public static void enet_peer_disconnect_now(ENetPeer* peer, uint data)
        {
            Platform.peer_disconnect_now(peer, data);
        }

        public static void enet_peer_disconnect_later(ENetPeer* peer, uint data)
        {
            Platform.peer_disconnect_later(peer, data);
        }

        public static void enet_peer_ping(ENetPeer* peer)
        {
            Platform.peer_ping(peer);
        }

        public static void enet_peer_ping_interval(ENetPeer* peer, uint pingInterval)
        {
            Platform.peer_ping_interval(peer, pingInterval);
        }

        public static ENetPacket* enet_peer_receive(ENetPeer* peer, out byte channelID)
        {
            return Platform.peer_receive(peer, out channelID);
        }

        public static void enet_peer_reset(ENetPeer* peer)
        {
            Platform.peer_reset(peer);
        }

        public static int enet_peer_send(ENetPeer* peer, byte channelID, ENetPacket* packet)
        {
            return Platform.peer_send(peer, channelID, packet);
        }

        public static void enet_peer_throttle_configure(ENetPeer* peer, uint interval, uint acceleration, uint deceleration)
        {
            Platform.peer_throttle_configure(peer, interval, acceleration, deceleration);
        }

        public static void enet_peer_timeout(ENetPeer* peer, uint timeoutLimit, uint timeoutMinimum, uint timeoutMaximum)
        {
            Platform.peer_timeout(peer, timeoutLimit, timeoutMinimum, timeoutMaximum);
        }

        public abstract void peer_disconnect(ENetPeer* peer, uint data);

        public abstract void peer_disconnect_now(ENetPeer* peer, uint data);

        public abstract void peer_disconnect_later(ENetPeer* peer, uint data);

        public abstract void peer_ping(ENetPeer* peer);

        public abstract void peer_ping_interval(ENetPeer* peer, uint pingInterval);

        public abstract ENetPacket* peer_receive(ENetPeer* peer, out byte channelID);

        public abstract void peer_reset(ENetPeer* peer);

        public abstract int peer_send(ENetPeer* peer, byte channelID, ENetPacket* packet);

        public abstract void peer_throttle_configure(ENetPeer* peer, uint interval, uint acceleration, uint deceleration);

        public abstract void peer_timeout(ENetPeer* peer, uint timeoutLimit, uint timeoutMinimum, uint timeoutMaximum);
        #endregion

        #region C# Utility
        public static bool memcmp(byte[] s1, byte[] s2)
        {
            if (s1 == null || s2 == null) { throw new ArgumentNullException(); }
            if (s1.Length != s2.Length) { return false; }

            for (int i = 0; i < s1.Length; i++) { if (s1[i] != s2[i]) { return false; } }
            return true;
        }

        public static int strlen(byte[] s)
        {
            if (s == null) { throw new ArgumentNullException(); }

            int i;
            for (i = 0; i < s.Length && s[i] != 0; i++) ;
            return i;
        }
        #endregion
    }
}
