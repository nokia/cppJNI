#pragma once

#include "deferred_call.hpp"
#include "list.hpp"

namespace cppjni
{
namespace mpl
{
    namespace detail
    {
        enum class JoinSize {SIZE_4, SIZE_16, SIZE_64, SIZE_256, SIZE_ANY};
        
        constexpr JoinSize selectJoinSize(unsigned size)
        {
            return 
                size <= 4
                    ? JoinSize::SIZE_4 
                    : size <= 16
                        ? JoinSize::SIZE_16
                        : size <= 64
                            ? JoinSize::SIZE_64
                            : size <= 256
                                ? JoinSize::SIZE_256
                                : JoinSize::SIZE_ANY
            ;
        }
        
        template<JoinSize>
        struct join_impl;
        
        template<>
        struct join_impl<JoinSize::SIZE_4>
        {
            template<typename = list<>, typename = list<>, typename = list<>, typename = list<>>
            struct split;
            
            template<typename... L0x00, typename... L0x01, typename... L0x02, typename... L0x03>
            struct split<list<L0x00...>, list<L0x01...>, list<L0x02...>, list<L0x03...>>
            {
                template<typename C>
                using f = typename C::template f<L0x00..., L0x01..., L0x02..., L0x03...>;
            };
        };
        
        template<>
        struct join_impl<JoinSize::SIZE_16>
        {
            template<
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>
            >
            struct split;
            
            template<
                    typename... L0x00, typename... L0x01, typename... L0x02, typename... L0x03
                ,   typename... L0x04, typename... L0x05, typename... L0x06, typename... L0x07
                ,   typename... L0x08, typename... L0x09, typename... L0x0A, typename... L0x0B
                ,   typename... L0x0C, typename... L0x0D, typename... L0x0E, typename... L0x0F
            >
            struct split<
                    list<L0x00...>,   list<L0x01...>,   list<L0x02...>,   list<L0x03...>
                ,   list<L0x04...>,   list<L0x05...>,   list<L0x06...>,   list<L0x07...>
                ,   list<L0x08...>,   list<L0x09...>,   list<L0x0A...>,   list<L0x0B...>
                ,   list<L0x0C...>,   list<L0x0D...>,   list<L0x0E...>,   list<L0x0F...>
            >
            {
                template<typename C>
                using f = typename C::template f<
                        L0x00..., L0x01..., L0x02..., L0x03...
                    ,   L0x04..., L0x05..., L0x06..., L0x07...
                    ,   L0x08..., L0x09..., L0x0A..., L0x0B...
                    ,   L0x0C..., L0x0D..., L0x0E..., L0x0F...
                >;
            };
        };
        
        template<>
        struct join_impl<JoinSize::SIZE_64>
        {
            template<
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, 
                typename = list<>, typename = list<>, typename = list<>, typename = list<>
            >
            struct split;
            
            template<
                  typename... L0x00, typename... L0x01, typename... L0x02, typename... L0x03, typename... L0x04, typename... L0x05, typename... L0x06, typename... L0x07, typename... L0x0C, typename... L0x0D, typename... L0x0E, typename... L0x0F, typename... L0x08, typename... L0x09, typename... L0x0A, typename... L0x0B
                , typename... L0x10, typename... L0x11, typename... L0x12, typename... L0x13, typename... L0x14, typename... L0x15, typename... L0x16, typename... L0x17, typename... L0x18, typename... L0x19, typename... L0x1A, typename... L0x1B, typename... L0x1C, typename... L0x1D, typename... L0x1E, typename... L0x1F
                , typename... L0x20, typename... L0x21, typename... L0x22, typename... L0x23, typename... L0x24, typename... L0x25, typename... L0x26, typename... L0x27, typename... L0x28, typename... L0x29, typename... L0x2A, typename... L0x2B, typename... L0x2C, typename... L0x2D, typename... L0x2E, typename... L0x2F
                , typename... L0x30, typename... L0x31, typename... L0x32, typename... L0x33, typename... L0x34, typename... L0x35, typename... L0x36, typename... L0x37, typename... L0x38, typename... L0x39, typename... L0x3A, typename... L0x3B, typename... L0x3C, typename... L0x3D, typename... L0x3E, typename... L0x3F
            >
            struct split<
                  list<L0x00...>,   list<L0x01...>,   list<L0x02...>,   list<L0x03...>, list<L0x04...>,   list<L0x05...>,   list<L0x06...>,   list<L0x07...>, list<L0x08...>,   list<L0x09...>,   list<L0x0A...>,   list<L0x0B...>, list<L0x0C...>,   list<L0x0D...>,   list<L0x0E...>,   list<L0x0F...>
                , list<L0x10...>,   list<L0x11...>,   list<L0x12...>,   list<L0x13...>, list<L0x14...>,   list<L0x15...>,   list<L0x16...>,   list<L0x17...>, list<L0x18...>,   list<L0x19...>,   list<L0x1A...>,   list<L0x1B...>, list<L0x1C...>,   list<L0x1D...>,   list<L0x1E...>,   list<L0x1F...>
                , list<L0x20...>,   list<L0x21...>,   list<L0x22...>,   list<L0x23...>, list<L0x24...>,   list<L0x25...>,   list<L0x26...>,   list<L0x27...>, list<L0x28...>,   list<L0x29...>,   list<L0x2A...>,   list<L0x2B...>, list<L0x2C...>,   list<L0x2D...>,   list<L0x2E...>,   list<L0x2F...>
                , list<L0x30...>,   list<L0x31...>,   list<L0x32...>,   list<L0x33...>, list<L0x34...>,   list<L0x35...>,   list<L0x36...>,   list<L0x37...>, list<L0x38...>,   list<L0x39...>,   list<L0x3A...>,   list<L0x3B...>, list<L0x3C...>,   list<L0x3D...>,   list<L0x3E...>,   list<L0x3F...>
            >
            {
                template<typename C>
                using f = typename C::template f<
                      L0x00..., L0x01..., L0x02..., L0x03..., L0x04..., L0x05..., L0x06..., L0x07..., L0x08..., L0x09..., L0x0A..., L0x0B..., L0x0C..., L0x0D..., L0x0E..., L0x0F...
                    , L0x10..., L0x11..., L0x12..., L0x13..., L0x14..., L0x15..., L0x16..., L0x17..., L0x18..., L0x19..., L0x1A..., L0x1B..., L0x1C..., L0x1D..., L0x1E..., L0x1F...
                    , L0x20..., L0x21..., L0x22..., L0x23..., L0x24..., L0x25..., L0x26..., L0x27..., L0x28..., L0x29..., L0x2A..., L0x2B..., L0x2C..., L0x2D..., L0x2E..., L0x2F...
                    , L0x30..., L0x31..., L0x32..., L0x33..., L0x34..., L0x35..., L0x36..., L0x37..., L0x38..., L0x39..., L0x3A..., L0x3B..., L0x3C..., L0x3D..., L0x3E..., L0x3F...
                >;
            };
        };
        
        template<>
        struct join_impl<JoinSize::SIZE_256>
        {
            template<
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>
            >
            struct split;
            
            template<
                  typename... L0x00, typename... L0x01, typename... L0x02, typename... L0x03, typename... L0x04, typename... L0x05, typename... L0x06, typename... L0x07, typename... L0x08, typename... L0x09, typename... L0x0A, typename... L0x0B, typename... L0x0C, typename... L0x0D, typename... L0x0E, typename... L0x0F
                , typename... L0x10, typename... L0x11, typename... L0x12, typename... L0x13, typename... L0x14, typename... L0x15, typename... L0x16, typename... L0x17, typename... L0x18, typename... L0x19, typename... L0x1A, typename... L0x1B, typename... L0x1C, typename... L0x1D, typename... L0x1E, typename... L0x1F
                , typename... L0x20, typename... L0x21, typename... L0x22, typename... L0x23, typename... L0x24, typename... L0x25, typename... L0x26, typename... L0x27, typename... L0x28, typename... L0x29, typename... L0x2A, typename... L0x2B, typename... L0x2C, typename... L0x2D, typename... L0x2E, typename... L0x2F
                , typename... L0x30, typename... L0x31, typename... L0x32, typename... L0x33, typename... L0x34, typename... L0x35, typename... L0x36, typename... L0x37, typename... L0x38, typename... L0x39, typename... L0x3A, typename... L0x3B, typename... L0x3C, typename... L0x3D, typename... L0x3E, typename... L0x3F
                , typename... L0x40, typename... L0x41, typename... L0x42, typename... L0x43, typename... L0x44, typename... L0x45, typename... L0x46, typename... L0x47, typename... L0x48, typename... L0x49, typename... L0x4A, typename... L0x4B, typename... L0x4C, typename... L0x4D, typename... L0x4E, typename... L0x4F
                , typename... L0x50, typename... L0x51, typename... L0x52, typename... L0x53, typename... L0x54, typename... L0x55, typename... L0x56, typename... L0x57, typename... L0x58, typename... L0x59, typename... L0x5A, typename... L0x5B, typename... L0x5C, typename... L0x5D, typename... L0x5E, typename... L0x5F
                , typename... L0x60, typename... L0x61, typename... L0x62, typename... L0x63, typename... L0x64, typename... L0x65, typename... L0x66, typename... L0x67, typename... L0x68, typename... L0x69, typename... L0x6A, typename... L0x6B, typename... L0x6C, typename... L0x6D, typename... L0x6E, typename... L0x6F
                , typename... L0x70, typename... L0x71, typename... L0x72, typename... L0x73, typename... L0x74, typename... L0x75, typename... L0x76, typename... L0x77, typename... L0x78, typename... L0x79, typename... L0x7A, typename... L0x7B, typename... L0x7C, typename... L0x7D, typename... L0x7E, typename... L0x7F
                , typename... L0x80, typename... L0x81, typename... L0x82, typename... L0x83, typename... L0x84, typename... L0x85, typename... L0x86, typename... L0x87, typename... L0x88, typename... L0x89, typename... L0x8A, typename... L0x8B, typename... L0x8C, typename... L0x8D, typename... L0x8E, typename... L0x8F
                , typename... L0x90, typename... L0x91, typename... L0x92, typename... L0x93, typename... L0x94, typename... L0x95, typename... L0x96, typename... L0x97, typename... L0x98, typename... L0x99, typename... L0x9A, typename... L0x9B, typename... L0x9C, typename... L0x9D, typename... L0x9E, typename... L0x9F
                , typename... L0xA0, typename... L0xA1, typename... L0xA2, typename... L0xA3, typename... L0xA4, typename... L0xA5, typename... L0xA6, typename... L0xA7, typename... L0xA8, typename... L0xA9, typename... L0xAA, typename... L0xAB, typename... L0xAC, typename... L0xAD, typename... L0xAE, typename... L0xAF
                , typename... L0xB0, typename... L0xB1, typename... L0xB2, typename... L0xB3, typename... L0xB4, typename... L0xB5, typename... L0xB6, typename... L0xB7, typename... L0xB8, typename... L0xB9, typename... L0xBA, typename... L0xBB, typename... L0xBC, typename... L0xBD, typename... L0xBE, typename... L0xBF
                , typename... L0xC0, typename... L0xC1, typename... L0xC2, typename... L0xC3, typename... L0xC4, typename... L0xC5, typename... L0xC6, typename... L0xC7, typename... L0xC8, typename... L0xC9, typename... L0xCA, typename... L0xCB, typename... L0xCC, typename... L0xCD, typename... L0xCE, typename... L0xCF
                , typename... L0xD0, typename... L0xD1, typename... L0xD2, typename... L0xD3, typename... L0xD4, typename... L0xD5, typename... L0xD6, typename... L0xD7, typename... L0xD8, typename... L0xD9, typename... L0xDA, typename... L0xDB, typename... L0xDC, typename... L0xDD, typename... L0xDE, typename... L0xDF
                , typename... L0xE0, typename... L0xE1, typename... L0xE2, typename... L0xE3, typename... L0xE4, typename... L0xE5, typename... L0xE6, typename... L0xE7, typename... L0xE8, typename... L0xE9, typename... L0xEA, typename... L0xEB, typename... L0xEC, typename... L0xED, typename... L0xEE, typename... L0xEF
                , typename... L0xF0, typename... L0xF1, typename... L0xF2, typename... L0xF3, typename... L0xF4, typename... L0xF5, typename... L0xF6, typename... L0xF7, typename... L0xF8, typename... L0xF9, typename... L0xFA, typename... L0xFB, typename... L0xFC, typename... L0xFD, typename... L0xFE, typename... L0xFF
            >
            struct split<
                  list<L0x00...>, list<L0x01...>, list<L0x02...>, list<L0x03...>, list<L0x04...>, list<L0x05...>, list<L0x06...>, list<L0x07...>, list<L0x08...>, list<L0x09...>, list<L0x0A...>, list<L0x0B...>, list<L0x0C...>, list<L0x0D...>, list<L0x0E...>, list<L0x0F...>
                , list<L0x10...>, list<L0x11...>, list<L0x12...>, list<L0x13...>, list<L0x14...>, list<L0x15...>, list<L0x16...>, list<L0x17...>, list<L0x18...>, list<L0x19...>, list<L0x1A...>, list<L0x1B...>, list<L0x1C...>, list<L0x1D...>, list<L0x1E...>, list<L0x1F...>
                , list<L0x20...>, list<L0x21...>, list<L0x22...>, list<L0x23...>, list<L0x24...>, list<L0x25...>, list<L0x26...>, list<L0x27...>, list<L0x28...>, list<L0x29...>, list<L0x2A...>, list<L0x2B...>, list<L0x2C...>, list<L0x2D...>, list<L0x2E...>, list<L0x2F...>
                , list<L0x30...>, list<L0x31...>, list<L0x32...>, list<L0x33...>, list<L0x34...>, list<L0x35...>, list<L0x36...>, list<L0x37...>, list<L0x38...>, list<L0x39...>, list<L0x3A...>, list<L0x3B...>, list<L0x3C...>, list<L0x3D...>, list<L0x3E...>, list<L0x3F...>
                , list<L0x40...>, list<L0x41...>, list<L0x42...>, list<L0x43...>, list<L0x44...>, list<L0x45...>, list<L0x46...>, list<L0x47...>, list<L0x48...>, list<L0x49...>, list<L0x4A...>, list<L0x4B...>, list<L0x4C...>, list<L0x4D...>, list<L0x4E...>, list<L0x4F...>
                , list<L0x50...>, list<L0x51...>, list<L0x52...>, list<L0x53...>, list<L0x54...>, list<L0x55...>, list<L0x56...>, list<L0x57...>, list<L0x58...>, list<L0x59...>, list<L0x5A...>, list<L0x5B...>, list<L0x5C...>, list<L0x5D...>, list<L0x5E...>, list<L0x5F...>
                , list<L0x60...>, list<L0x61...>, list<L0x62...>, list<L0x63...>, list<L0x64...>, list<L0x65...>, list<L0x66...>, list<L0x67...>, list<L0x68...>, list<L0x69...>, list<L0x6A...>, list<L0x6B...>, list<L0x6C...>, list<L0x6D...>, list<L0x6E...>, list<L0x6F...>
                , list<L0x70...>, list<L0x71...>, list<L0x72...>, list<L0x73...>, list<L0x74...>, list<L0x75...>, list<L0x76...>, list<L0x77...>, list<L0x78...>, list<L0x79...>, list<L0x7A...>, list<L0x7B...>, list<L0x7C...>, list<L0x7D...>, list<L0x7E...>, list<L0x7F...>
                , list<L0x80...>, list<L0x81...>, list<L0x82...>, list<L0x83...>, list<L0x84...>, list<L0x85...>, list<L0x86...>, list<L0x87...>, list<L0x88...>, list<L0x89...>, list<L0x8A...>, list<L0x8B...>, list<L0x8C...>, list<L0x8D...>, list<L0x8E...>, list<L0x8F...>
                , list<L0x90...>, list<L0x91...>, list<L0x92...>, list<L0x93...>, list<L0x94...>, list<L0x95...>, list<L0x96...>, list<L0x97...>, list<L0x98...>, list<L0x99...>, list<L0x9A...>, list<L0x9B...>, list<L0x9C...>, list<L0x9D...>, list<L0x9E...>, list<L0x9F...>
                , list<L0xA0...>, list<L0xA1...>, list<L0xA2...>, list<L0xA3...>, list<L0xA4...>, list<L0xA5...>, list<L0xA6...>, list<L0xA7...>, list<L0xA8...>, list<L0xA9...>, list<L0xAA...>, list<L0xAB...>, list<L0xAC...>, list<L0xAD...>, list<L0xAE...>, list<L0xAF...>
                , list<L0xB0...>, list<L0xB1...>, list<L0xB2...>, list<L0xB3...>, list<L0xB4...>, list<L0xB5...>, list<L0xB6...>, list<L0xB7...>, list<L0xB8...>, list<L0xB9...>, list<L0xBA...>, list<L0xBB...>, list<L0xBC...>, list<L0xBD...>, list<L0xBE...>, list<L0xBF...>
                , list<L0xC0...>, list<L0xC1...>, list<L0xC2...>, list<L0xC3...>, list<L0xC4...>, list<L0xC5...>, list<L0xC6...>, list<L0xC7...>, list<L0xC8...>, list<L0xC9...>, list<L0xCA...>, list<L0xCB...>, list<L0xCC...>, list<L0xCD...>, list<L0xCE...>, list<L0xCF...>
                , list<L0xD0...>, list<L0xD1...>, list<L0xD2...>, list<L0xD3...>, list<L0xD4...>, list<L0xD5...>, list<L0xD6...>, list<L0xD7...>, list<L0xD8...>, list<L0xD9...>, list<L0xDA...>, list<L0xDB...>, list<L0xDC...>, list<L0xDD...>, list<L0xDE...>, list<L0xDF...>
                , list<L0xE0...>, list<L0xE1...>, list<L0xE2...>, list<L0xE3...>, list<L0xE4...>, list<L0xE5...>, list<L0xE6...>, list<L0xE7...>, list<L0xE8...>, list<L0xE9...>, list<L0xEA...>, list<L0xEB...>, list<L0xEC...>, list<L0xED...>, list<L0xEE...>, list<L0xEF...>
                , list<L0xF0...>, list<L0xF1...>, list<L0xF2...>, list<L0xF3...>, list<L0xF4...>, list<L0xF5...>, list<L0xF6...>, list<L0xF7...>, list<L0xF8...>, list<L0xF9...>, list<L0xFA...>, list<L0xFB...>, list<L0xFC...>, list<L0xFD...>, list<L0xFE...>, list<L0xFF...>
            >
            {
                template<typename C>
                using f =
                    typename C::template f<
                            L0x00..., L0x01..., L0x02..., L0x03..., L0x04..., L0x05..., L0x06..., L0x07..., L0x08..., L0x09..., L0x0A..., L0x0B..., L0x0C..., L0x0D..., L0x0E..., L0x0F...
                        , L0x10..., L0x11..., L0x12..., L0x13..., L0x14..., L0x15..., L0x16..., L0x17..., L0x18..., L0x19..., L0x1A..., L0x1B..., L0x1C..., L0x1D..., L0x1E..., L0x1F...
                        , L0x20..., L0x21..., L0x22..., L0x23..., L0x24..., L0x25..., L0x26..., L0x27..., L0x28..., L0x29..., L0x2A..., L0x2B..., L0x2C..., L0x2D..., L0x2E..., L0x2F...
                        , L0x30..., L0x31..., L0x32..., L0x33..., L0x34..., L0x35..., L0x36..., L0x37..., L0x38..., L0x39..., L0x3A..., L0x3B..., L0x3C..., L0x3D..., L0x3E..., L0x3F...
                        , L0x40..., L0x41..., L0x42..., L0x43..., L0x44..., L0x45..., L0x46..., L0x47..., L0x48..., L0x49..., L0x4A..., L0x4B..., L0x4C..., L0x4D..., L0x4E..., L0x4F...
                        , L0x50..., L0x51..., L0x52..., L0x53..., L0x54..., L0x55..., L0x56..., L0x57..., L0x58..., L0x59..., L0x5A..., L0x5B..., L0x5C..., L0x5D..., L0x5E..., L0x5F...
                        , L0x60..., L0x61..., L0x62..., L0x63..., L0x64..., L0x65..., L0x66..., L0x67..., L0x68..., L0x69..., L0x6A..., L0x6B..., L0x6C..., L0x6D..., L0x6E..., L0x6F...
                        , L0x70..., L0x71..., L0x72..., L0x73..., L0x74..., L0x75..., L0x76..., L0x77..., L0x78..., L0x79..., L0x7A..., L0x7B..., L0x7C..., L0x7D..., L0x7E..., L0x7F...
                        , L0x80..., L0x81..., L0x82..., L0x83..., L0x84..., L0x85..., L0x86..., L0x87..., L0x88..., L0x89..., L0x8A..., L0x8B..., L0x8C..., L0x8D..., L0x8E..., L0x8F...
                        , L0x90..., L0x91..., L0x92..., L0x93..., L0x94..., L0x95..., L0x96..., L0x97..., L0x98..., L0x99..., L0x9A..., L0x9B..., L0x9C..., L0x9D..., L0x9E..., L0x9F...
                        , L0xA0..., L0xA1..., L0xA2..., L0xA3..., L0xA4..., L0xA5..., L0xA6..., L0xA7..., L0xA8..., L0xA9..., L0xAA..., L0xAB..., L0xAC..., L0xAD..., L0xAE..., L0xAF...
                        , L0xB0..., L0xB1..., L0xB2..., L0xB3..., L0xB4..., L0xB5..., L0xB6..., L0xB7..., L0xB8..., L0xB9..., L0xBA..., L0xBB..., L0xBC..., L0xBD..., L0xBE..., L0xBF...
                        , L0xC0..., L0xC1..., L0xC2..., L0xC3..., L0xC4..., L0xC5..., L0xC6..., L0xC7..., L0xC8..., L0xC9..., L0xCA..., L0xCB..., L0xCC..., L0xCD..., L0xCE..., L0xCF...
                        , L0xD0..., L0xD1..., L0xD2..., L0xD3..., L0xD4..., L0xD5..., L0xD6..., L0xD7..., L0xD8..., L0xD9..., L0xDA..., L0xDB..., L0xDC..., L0xDD..., L0xDE..., L0xDF...
                        , L0xE0..., L0xE1..., L0xE2..., L0xE3..., L0xE4..., L0xE5..., L0xE6..., L0xE7..., L0xE8..., L0xE9..., L0xEA..., L0xEB..., L0xEC..., L0xED..., L0xEE..., L0xEF...
                        , L0xF0..., L0xF1..., L0xF2..., L0xF3..., L0xF4..., L0xF5..., L0xF6..., L0xF7..., L0xF8..., L0xF9..., L0xFA..., L0xFB..., L0xFC..., L0xFD..., L0xFE..., L0xFF...
                    >;
            };
        };
        
        template<>
        struct join_impl<JoinSize::SIZE_ANY>
        {
            template<
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>,
                typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>, typename = list<>
            >
            struct split;
            
            template<
                  typename... L0x000, typename... L0x001, typename... L0x002, typename... L0x003, typename... L0x004, typename... L0x005, typename... L0x006, typename... L0x007, typename... L0x008, typename... L0x009, typename... L0x00A, typename... L0x00B, typename... L0x00C, typename... L0x00D, typename... L0x00E, typename... L0x00F
                , typename... L0x010, typename... L0x011, typename... L0x012, typename... L0x013, typename... L0x014, typename... L0x015, typename... L0x016, typename... L0x017, typename... L0x018, typename... L0x019, typename... L0x01A, typename... L0x01B, typename... L0x01C, typename... L0x01D, typename... L0x01E, typename... L0x01F
                , typename... L0x020, typename... L0x021, typename... L0x022, typename... L0x023, typename... L0x024, typename... L0x025, typename... L0x026, typename... L0x027, typename... L0x028, typename... L0x029, typename... L0x02A, typename... L0x02B, typename... L0x02C, typename... L0x02D, typename... L0x02E, typename... L0x02F
                , typename... L0x030, typename... L0x031, typename... L0x032, typename... L0x033, typename... L0x034, typename... L0x035, typename... L0x036, typename... L0x037, typename... L0x038, typename... L0x039, typename... L0x03A, typename... L0x03B, typename... L0x03C, typename... L0x03D, typename... L0x03E, typename... L0x03F
                , typename... L0x040, typename... L0x041, typename... L0x042, typename... L0x043, typename... L0x044, typename... L0x045, typename... L0x046, typename... L0x047, typename... L0x048, typename... L0x049, typename... L0x04A, typename... L0x04B, typename... L0x04C, typename... L0x04D, typename... L0x04E, typename... L0x04F
                , typename... L0x050, typename... L0x051, typename... L0x052, typename... L0x053, typename... L0x054, typename... L0x055, typename... L0x056, typename... L0x057, typename... L0x058, typename... L0x059, typename... L0x05A, typename... L0x05B, typename... L0x05C, typename... L0x05D, typename... L0x05E, typename... L0x05F
                , typename... L0x060, typename... L0x061, typename... L0x062, typename... L0x063, typename... L0x064, typename... L0x065, typename... L0x066, typename... L0x067, typename... L0x068, typename... L0x069, typename... L0x06A, typename... L0x06B, typename... L0x06C, typename... L0x06D, typename... L0x06E, typename... L0x06F
                , typename... L0x070, typename... L0x071, typename... L0x072, typename... L0x073, typename... L0x074, typename... L0x075, typename... L0x076, typename... L0x077, typename... L0x078, typename... L0x079, typename... L0x07A, typename... L0x07B, typename... L0x07C, typename... L0x07D, typename... L0x07E, typename... L0x07F
                , typename... L0x080, typename... L0x081, typename... L0x082, typename... L0x083, typename... L0x084, typename... L0x085, typename... L0x086, typename... L0x087, typename... L0x088, typename... L0x089, typename... L0x08A, typename... L0x08B, typename... L0x08C, typename... L0x08D, typename... L0x08E, typename... L0x08F
                , typename... L0x090, typename... L0x091, typename... L0x092, typename... L0x093, typename... L0x094, typename... L0x095, typename... L0x096, typename... L0x097, typename... L0x098, typename... L0x099, typename... L0x09A, typename... L0x09B, typename... L0x09C, typename... L0x09D, typename... L0x09E, typename... L0x09F
                , typename... L0x0A0, typename... L0x0A1, typename... L0x0A2, typename... L0x0A3, typename... L0x0A4, typename... L0x0A5, typename... L0x0A6, typename... L0x0A7, typename... L0x0A8, typename... L0x0A9, typename... L0x0AA, typename... L0x0AB, typename... L0x0AC, typename... L0x0AD, typename... L0x0AE, typename... L0x0AF
                , typename... L0x0B0, typename... L0x0B1, typename... L0x0B2, typename... L0x0B3, typename... L0x0B4, typename... L0x0B5, typename... L0x0B6, typename... L0x0B7, typename... L0x0B8, typename... L0x0B9, typename... L0x0BA, typename... L0x0BB, typename... L0x0BC, typename... L0x0BD, typename... L0x0BE, typename... L0x0BF
                , typename... L0x0C0, typename... L0x0C1, typename... L0x0C2, typename... L0x0C3, typename... L0x0C4, typename... L0x0C5, typename... L0x0C6, typename... L0x0C7, typename... L0x0C8, typename... L0x0C9, typename... L0x0CA, typename... L0x0CB, typename... L0x0CC, typename... L0x0CD, typename... L0x0CE, typename... L0x0CF
                , typename... L0x0D0, typename... L0x0D1, typename... L0x0D2, typename... L0x0D3, typename... L0x0D4, typename... L0x0D5, typename... L0x0D6, typename... L0x0D7, typename... L0x0D8, typename... L0x0D9, typename... L0x0DA, typename... L0x0DB, typename... L0x0DC, typename... L0x0DD, typename... L0x0DE, typename... L0x0DF
                , typename... L0x0E0, typename... L0x0E1, typename... L0x0E2, typename... L0x0E3, typename... L0x0E4, typename... L0x0E5, typename... L0x0E6, typename... L0x0E7, typename... L0x0E8, typename... L0x0E9, typename... L0x0EA, typename... L0x0EB, typename... L0x0EC, typename... L0x0ED, typename... L0x0EE, typename... L0x0EF
                , typename... L0x0F0, typename... L0x0F1, typename... L0x0F2, typename... L0x0F3, typename... L0x0F4, typename... L0x0F5, typename... L0x0F6, typename... L0x0F7, typename... L0x0F8, typename... L0x0F9, typename... L0x0FA, typename... L0x0FB, typename... L0x0FC, typename... L0x0FD, typename... L0x0FE, typename... L0x0FF
            
                , typename... L0x100, typename... L0x101, typename... L0x102, typename... L0x103, typename... L0x104, typename... L0x105, typename... L0x106, typename... L0x107, typename... L0x108, typename... L0x109, typename... L0x10A, typename... L0x10B, typename... L0x10C, typename... L0x10D, typename... L0x10E, typename... L0x10F
                , typename... L0x110, typename... L0x111, typename... L0x112, typename... L0x113, typename... L0x114, typename... L0x115, typename... L0x116, typename... L0x117, typename... L0x118, typename... L0x119, typename... L0x11A, typename... L0x11B, typename... L0x11C, typename... L0x11D, typename... L0x11E, typename... L0x11F
                , typename... L0x120, typename... L0x121, typename... L0x122, typename... L0x123, typename... L0x124, typename... L0x125, typename... L0x126, typename... L0x127, typename... L0x128, typename... L0x129, typename... L0x12A, typename... L0x12B, typename... L0x12C, typename... L0x12D, typename... L0x12E, typename... L0x12F
                , typename... L0x130, typename... L0x131, typename... L0x132, typename... L0x133, typename... L0x134, typename... L0x135, typename... L0x136, typename... L0x137, typename... L0x138, typename... L0x139, typename... L0x13A, typename... L0x13B, typename... L0x13C, typename... L0x13D, typename... L0x13E, typename... L0x13F
                , typename... L0x140, typename... L0x141, typename... L0x142, typename... L0x143, typename... L0x144, typename... L0x145, typename... L0x146, typename... L0x147, typename... L0x148, typename... L0x149, typename... L0x14A, typename... L0x14B, typename... L0x14C, typename... L0x14D, typename... L0x14E, typename... L0x14F
                , typename... L0x150, typename... L0x151, typename... L0x152, typename... L0x153, typename... L0x154, typename... L0x155, typename... L0x156, typename... L0x157, typename... L0x158, typename... L0x159, typename... L0x15A, typename... L0x15B, typename... L0x15C, typename... L0x15D, typename... L0x15E, typename... L0x15F
                , typename... L0x160, typename... L0x161, typename... L0x162, typename... L0x163, typename... L0x164, typename... L0x165, typename... L0x166, typename... L0x167, typename... L0x168, typename... L0x169, typename... L0x16A, typename... L0x16B, typename... L0x16C, typename... L0x16D, typename... L0x16E, typename... L0x16F
                , typename... L0x170, typename... L0x171, typename... L0x172, typename... L0x173, typename... L0x174, typename... L0x175, typename... L0x176, typename... L0x177, typename... L0x178, typename... L0x179, typename... L0x17A, typename... L0x17B, typename... L0x17C, typename... L0x17D, typename... L0x17E, typename... L0x17F
                , typename... L0x180, typename... L0x181, typename... L0x182, typename... L0x183, typename... L0x184, typename... L0x185, typename... L0x186, typename... L0x187, typename... L0x188, typename... L0x189, typename... L0x18A, typename... L0x18B, typename... L0x18C, typename... L0x18D, typename... L0x18E, typename... L0x18F
                , typename... L0x190, typename... L0x191, typename... L0x192, typename... L0x193, typename... L0x194, typename... L0x195, typename... L0x196, typename... L0x197, typename... L0x198, typename... L0x199, typename... L0x19A, typename... L0x19B, typename... L0x19C, typename... L0x19D, typename... L0x19E, typename... L0x19F
                , typename... L0x1A0, typename... L0x1A1, typename... L0x1A2, typename... L0x1A3, typename... L0x1A4, typename... L0x1A5, typename... L0x1A6, typename... L0x1A7, typename... L0x1A8, typename... L0x1A9, typename... L0x1AA, typename... L0x1AB, typename... L0x1AC, typename... L0x1AD, typename... L0x1AE, typename... L0x1AF
                , typename... L0x1B0, typename... L0x1B1, typename... L0x1B2, typename... L0x1B3, typename... L0x1B4, typename... L0x1B5, typename... L0x1B6, typename... L0x1B7, typename... L0x1B8, typename... L0x1B9, typename... L0x1BA, typename... L0x1BB, typename... L0x1BC, typename... L0x1BD, typename... L0x1BE, typename... L0x1BF
                , typename... L0x1C0, typename... L0x1C1, typename... L0x1C2, typename... L0x1C3, typename... L0x1C4, typename... L0x1C5, typename... L0x1C6, typename... L0x1C7, typename... L0x1C8, typename... L0x1C9, typename... L0x1CA, typename... L0x1CB, typename... L0x1CC, typename... L0x1CD, typename... L0x1CE, typename... L0x1CF
                , typename... L0x1D0, typename... L0x1D1, typename... L0x1D2, typename... L0x1D3, typename... L0x1D4, typename... L0x1D5, typename... L0x1D6, typename... L0x1D7, typename... L0x1D8, typename... L0x1D9, typename... L0x1DA, typename... L0x1DB, typename... L0x1DC, typename... L0x1DD, typename... L0x1DE, typename... L0x1DF
                , typename... L0x1E0, typename... L0x1E1, typename... L0x1E2, typename... L0x1E3, typename... L0x1E4, typename... L0x1E5, typename... L0x1E6, typename... L0x1E7, typename... L0x1E8, typename... L0x1E9, typename... L0x1EA, typename... L0x1EB, typename... L0x1EC, typename... L0x1ED, typename... L0x1EE, typename... L0x1EF
                , typename... L0x1F0, typename... L0x1F1, typename... L0x1F2, typename... L0x1F3, typename... L0x1F4, typename... L0x1F5, typename... L0x1F6, typename... L0x1F7, typename... L0x1F8, typename... L0x1F9, typename... L0x1FA, typename... L0x1FB, typename... L0x1FC, typename... L0x1FD, typename... L0x1FE, typename... L0x1FF
            
                , typename... L0x200, typename... L0x201, typename... L0x202, typename... L0x203, typename... L0x204, typename... L0x205, typename... L0x206, typename... L0x207, typename... L0x208, typename... L0x209, typename... L0x20A, typename... L0x20B, typename... L0x20C, typename... L0x20D, typename... L0x20E, typename... L0x20F
                , typename... L0x210, typename... L0x211, typename... L0x212, typename... L0x213, typename... L0x214, typename... L0x215, typename... L0x216, typename... L0x217, typename... L0x218, typename... L0x219, typename... L0x21A, typename... L0x21B, typename... L0x21C, typename... L0x21D, typename... L0x21E, typename... L0x21F
                , typename... L0x220, typename... L0x221, typename... L0x222, typename... L0x223, typename... L0x224, typename... L0x225, typename... L0x226, typename... L0x227, typename... L0x228, typename... L0x229, typename... L0x22A, typename... L0x22B, typename... L0x22C, typename... L0x22D, typename... L0x22E, typename... L0x22F
                , typename... L0x230, typename... L0x231, typename... L0x232, typename... L0x233, typename... L0x234, typename... L0x235, typename... L0x236, typename... L0x237, typename... L0x238, typename... L0x239, typename... L0x23A, typename... L0x23B, typename... L0x23C, typename... L0x23D, typename... L0x23E, typename... L0x23F
                , typename... L0x240, typename... L0x241, typename... L0x242, typename... L0x243, typename... L0x244, typename... L0x245, typename... L0x246, typename... L0x247, typename... L0x248, typename... L0x249, typename... L0x24A, typename... L0x24B, typename... L0x24C, typename... L0x24D, typename... L0x24E, typename... L0x24F
                , typename... L0x250, typename... L0x251, typename... L0x252, typename... L0x253, typename... L0x254, typename... L0x255, typename... L0x256, typename... L0x257, typename... L0x258, typename... L0x259, typename... L0x25A, typename... L0x25B, typename... L0x25C, typename... L0x25D, typename... L0x25E, typename... L0x25F
                , typename... L0x260, typename... L0x261, typename... L0x262, typename... L0x263, typename... L0x264, typename... L0x265, typename... L0x266, typename... L0x267, typename... L0x268, typename... L0x269, typename... L0x26A, typename... L0x26B, typename... L0x26C, typename... L0x26D, typename... L0x26E, typename... L0x26F
                , typename... L0x270, typename... L0x271, typename... L0x272, typename... L0x273, typename... L0x274, typename... L0x275, typename... L0x276, typename... L0x277, typename... L0x278, typename... L0x279, typename... L0x27A, typename... L0x27B, typename... L0x27C, typename... L0x27D, typename... L0x27E, typename... L0x27F
                , typename... L0x280, typename... L0x281, typename... L0x282, typename... L0x283, typename... L0x284, typename... L0x285, typename... L0x286, typename... L0x287, typename... L0x288, typename... L0x289, typename... L0x28A, typename... L0x28B, typename... L0x28C, typename... L0x28D, typename... L0x28E, typename... L0x28F
                , typename... L0x290, typename... L0x291, typename... L0x292, typename... L0x293, typename... L0x294, typename... L0x295, typename... L0x296, typename... L0x297, typename... L0x298, typename... L0x299, typename... L0x29A, typename... L0x29B, typename... L0x29C, typename... L0x29D, typename... L0x29E, typename... L0x29F
                , typename... L0x2A0, typename... L0x2A1, typename... L0x2A2, typename... L0x2A3, typename... L0x2A4, typename... L0x2A5, typename... L0x2A6, typename... L0x2A7, typename... L0x2A8, typename... L0x2A9, typename... L0x2AA, typename... L0x2AB, typename... L0x2AC, typename... L0x2AD, typename... L0x2AE, typename... L0x2AF
                , typename... L0x2B0, typename... L0x2B1, typename... L0x2B2, typename... L0x2B3, typename... L0x2B4, typename... L0x2B5, typename... L0x2B6, typename... L0x2B7, typename... L0x2B8, typename... L0x2B9, typename... L0x2BA, typename... L0x2BB, typename... L0x2BC, typename... L0x2BD, typename... L0x2BE, typename... L0x2BF
                , typename... L0x2C0, typename... L0x2C1, typename... L0x2C2, typename... L0x2C3, typename... L0x2C4, typename... L0x2C5, typename... L0x2C6, typename... L0x2C7, typename... L0x2C8, typename... L0x2C9, typename... L0x2CA, typename... L0x2CB, typename... L0x2CC, typename... L0x2CD, typename... L0x2CE, typename... L0x2CF
                , typename... L0x2D0, typename... L0x2D1, typename... L0x2D2, typename... L0x2D3, typename... L0x2D4, typename... L0x2D5, typename... L0x2D6, typename... L0x2D7, typename... L0x2D8, typename... L0x2D9, typename... L0x2DA, typename... L0x2DB, typename... L0x2DC, typename... L0x2DD, typename... L0x2DE, typename... L0x2DF
                , typename... L0x2E0, typename... L0x2E1, typename... L0x2E2, typename... L0x2E3, typename... L0x2E4, typename... L0x2E5, typename... L0x2E6, typename... L0x2E7, typename... L0x2E8, typename... L0x2E9, typename... L0x2EA, typename... L0x2EB, typename... L0x2EC, typename... L0x2ED, typename... L0x2EE, typename... L0x2EF
                , typename... L0x2F0, typename... L0x2F1, typename... L0x2F2, typename... L0x2F3, typename... L0x2F4, typename... L0x2F5, typename... L0x2F6, typename... L0x2F7, typename... L0x2F8, typename... L0x2F9, typename... L0x2FA, typename... L0x2FB, typename... L0x2FC, typename... L0x2FD, typename... L0x2FE, typename... L0x2FF
            
                , typename... L0x300, typename... L0x301, typename... L0x302, typename... L0x303, typename... L0x304, typename... L0x305, typename... L0x306, typename... L0x307, typename... L0x308, typename... L0x309, typename... L0x30A, typename... L0x30B, typename... L0x30C, typename... L0x30D, typename... L0x30E, typename... L0x30F
                , typename... L0x310, typename... L0x311, typename... L0x312, typename... L0x313, typename... L0x314, typename... L0x315, typename... L0x316, typename... L0x317, typename... L0x318, typename... L0x319, typename... L0x31A, typename... L0x31B, typename... L0x31C, typename... L0x31D, typename... L0x31E, typename... L0x31F
                , typename... L0x320, typename... L0x321, typename... L0x322, typename... L0x323, typename... L0x324, typename... L0x325, typename... L0x326, typename... L0x327, typename... L0x328, typename... L0x329, typename... L0x32A, typename... L0x32B, typename... L0x32C, typename... L0x32D, typename... L0x32E, typename... L0x32F
                , typename... L0x330, typename... L0x331, typename... L0x332, typename... L0x333, typename... L0x334, typename... L0x335, typename... L0x336, typename... L0x337, typename... L0x338, typename... L0x339, typename... L0x33A, typename... L0x33B, typename... L0x33C, typename... L0x33D, typename... L0x33E, typename... L0x33F
                , typename... L0x340, typename... L0x341, typename... L0x342, typename... L0x343, typename... L0x344, typename... L0x345, typename... L0x346, typename... L0x347, typename... L0x348, typename... L0x349, typename... L0x34A, typename... L0x34B, typename... L0x34C, typename... L0x34D, typename... L0x34E, typename... L0x34F
                , typename... L0x350, typename... L0x351, typename... L0x352, typename... L0x353, typename... L0x354, typename... L0x355, typename... L0x356, typename... L0x357, typename... L0x358, typename... L0x359, typename... L0x35A, typename... L0x35B, typename... L0x35C, typename... L0x35D, typename... L0x35E, typename... L0x35F
                , typename... L0x360, typename... L0x361, typename... L0x362, typename... L0x363, typename... L0x364, typename... L0x365, typename... L0x366, typename... L0x367, typename... L0x368, typename... L0x369, typename... L0x36A, typename... L0x36B, typename... L0x36C, typename... L0x36D, typename... L0x36E, typename... L0x36F
                , typename... L0x370, typename... L0x371, typename... L0x372, typename... L0x373, typename... L0x374, typename... L0x375, typename... L0x376, typename... L0x377, typename... L0x378, typename... L0x379, typename... L0x37A, typename... L0x37B, typename... L0x37C, typename... L0x37D, typename... L0x37E, typename... L0x37F
                , typename... L0x380, typename... L0x381, typename... L0x382, typename... L0x383, typename... L0x384, typename... L0x385, typename... L0x386, typename... L0x387, typename... L0x388, typename... L0x389, typename... L0x38A, typename... L0x38B, typename... L0x38C, typename... L0x38D, typename... L0x38E, typename... L0x38F
                , typename... L0x390, typename... L0x391, typename... L0x392, typename... L0x393, typename... L0x394, typename... L0x395, typename... L0x396, typename... L0x397, typename... L0x398, typename... L0x399, typename... L0x39A, typename... L0x39B, typename... L0x39C, typename... L0x39D, typename... L0x39E, typename... L0x39F
                , typename... L0x3A0, typename... L0x3A1, typename... L0x3A2, typename... L0x3A3, typename... L0x3A4, typename... L0x3A5, typename... L0x3A6, typename... L0x3A7, typename... L0x3A8, typename... L0x3A9, typename... L0x3AA, typename... L0x3AB, typename... L0x3AC, typename... L0x3AD, typename... L0x3AE, typename... L0x3AF
                , typename... L0x3B0, typename... L0x3B1, typename... L0x3B2, typename... L0x3B3, typename... L0x3B4, typename... L0x3B5, typename... L0x3B6, typename... L0x3B7, typename... L0x3B8, typename... L0x3B9, typename... L0x3BA, typename... L0x3BB, typename... L0x3BC, typename... L0x3BD, typename... L0x3BE, typename... L0x3BF
                , typename... L0x3C0, typename... L0x3C1, typename... L0x3C2, typename... L0x3C3, typename... L0x3C4, typename... L0x3C5, typename... L0x3C6, typename... L0x3C7, typename... L0x3C8, typename... L0x3C9, typename... L0x3CA, typename... L0x3CB, typename... L0x3CC, typename... L0x3CD, typename... L0x3CE, typename... L0x3CF
                , typename... L0x3D0, typename... L0x3D1, typename... L0x3D2, typename... L0x3D3, typename... L0x3D4, typename... L0x3D5, typename... L0x3D6, typename... L0x3D7, typename... L0x3D8, typename... L0x3D9, typename... L0x3DA, typename... L0x3DB, typename... L0x3DC, typename... L0x3DD, typename... L0x3DE, typename... L0x3DF
                , typename... L0x3E0, typename... L0x3E1, typename... L0x3E2, typename... L0x3E3, typename... L0x3E4, typename... L0x3E5, typename... L0x3E6, typename... L0x3E7, typename... L0x3E8, typename... L0x3E9, typename... L0x3EA, typename... L0x3EB, typename... L0x3EC, typename... L0x3ED, typename... L0x3EE, typename... L0x3EF
                , typename... L0x3F0, typename... L0x3F1, typename... L0x3F2, typename... L0x3F3, typename... L0x3F4, typename... L0x3F5, typename... L0x3F6, typename... L0x3F7, typename... L0x3F8, typename... L0x3F9, typename... L0x3FA, typename... L0x3FB, typename... L0x3FC, typename... L0x3FD, typename... L0x3FE, typename... L0x3FF
            >
            struct split<
                  list<L0x000...>, list<L0x001...>, list<L0x002...>, list<L0x003...>, list<L0x004...>, list<L0x005...>, list<L0x006...>, list<L0x007...>, list<L0x008...>, list<L0x009...>, list<L0x00A...>, list<L0x00B...>, list<L0x00C...>, list<L0x00D...>, list<L0x00E...>, list<L0x00F...>
                , list<L0x010...>, list<L0x011...>, list<L0x012...>, list<L0x013...>, list<L0x014...>, list<L0x015...>, list<L0x016...>, list<L0x017...>, list<L0x018...>, list<L0x019...>, list<L0x01A...>, list<L0x01B...>, list<L0x01C...>, list<L0x01D...>, list<L0x01E...>, list<L0x01F...>
                , list<L0x020...>, list<L0x021...>, list<L0x022...>, list<L0x023...>, list<L0x024...>, list<L0x025...>, list<L0x026...>, list<L0x027...>, list<L0x028...>, list<L0x029...>, list<L0x02A...>, list<L0x02B...>, list<L0x02C...>, list<L0x02D...>, list<L0x02E...>, list<L0x02F...>
                , list<L0x030...>, list<L0x031...>, list<L0x032...>, list<L0x033...>, list<L0x034...>, list<L0x035...>, list<L0x036...>, list<L0x037...>, list<L0x038...>, list<L0x039...>, list<L0x03A...>, list<L0x03B...>, list<L0x03C...>, list<L0x03D...>, list<L0x03E...>, list<L0x03F...>
                , list<L0x040...>, list<L0x041...>, list<L0x042...>, list<L0x043...>, list<L0x044...>, list<L0x045...>, list<L0x046...>, list<L0x047...>, list<L0x048...>, list<L0x049...>, list<L0x04A...>, list<L0x04B...>, list<L0x04C...>, list<L0x04D...>, list<L0x04E...>, list<L0x04F...>
                , list<L0x050...>, list<L0x051...>, list<L0x052...>, list<L0x053...>, list<L0x054...>, list<L0x055...>, list<L0x056...>, list<L0x057...>, list<L0x058...>, list<L0x059...>, list<L0x05A...>, list<L0x05B...>, list<L0x05C...>, list<L0x05D...>, list<L0x05E...>, list<L0x05F...>
                , list<L0x060...>, list<L0x061...>, list<L0x062...>, list<L0x063...>, list<L0x064...>, list<L0x065...>, list<L0x066...>, list<L0x067...>, list<L0x068...>, list<L0x069...>, list<L0x06A...>, list<L0x06B...>, list<L0x06C...>, list<L0x06D...>, list<L0x06E...>, list<L0x06F...>
                , list<L0x070...>, list<L0x071...>, list<L0x072...>, list<L0x073...>, list<L0x074...>, list<L0x075...>, list<L0x076...>, list<L0x077...>, list<L0x078...>, list<L0x079...>, list<L0x07A...>, list<L0x07B...>, list<L0x07C...>, list<L0x07D...>, list<L0x07E...>, list<L0x07F...>
                , list<L0x080...>, list<L0x081...>, list<L0x082...>, list<L0x083...>, list<L0x084...>, list<L0x085...>, list<L0x086...>, list<L0x087...>, list<L0x088...>, list<L0x089...>, list<L0x08A...>, list<L0x08B...>, list<L0x08C...>, list<L0x08D...>, list<L0x08E...>, list<L0x08F...>
                , list<L0x090...>, list<L0x091...>, list<L0x092...>, list<L0x093...>, list<L0x094...>, list<L0x095...>, list<L0x096...>, list<L0x097...>, list<L0x098...>, list<L0x099...>, list<L0x09A...>, list<L0x09B...>, list<L0x09C...>, list<L0x09D...>, list<L0x09E...>, list<L0x09F...>
                , list<L0x0A0...>, list<L0x0A1...>, list<L0x0A2...>, list<L0x0A3...>, list<L0x0A4...>, list<L0x0A5...>, list<L0x0A6...>, list<L0x0A7...>, list<L0x0A8...>, list<L0x0A9...>, list<L0x0AA...>, list<L0x0AB...>, list<L0x0AC...>, list<L0x0AD...>, list<L0x0AE...>, list<L0x0AF...>
                , list<L0x0B0...>, list<L0x0B1...>, list<L0x0B2...>, list<L0x0B3...>, list<L0x0B4...>, list<L0x0B5...>, list<L0x0B6...>, list<L0x0B7...>, list<L0x0B8...>, list<L0x0B9...>, list<L0x0BA...>, list<L0x0BB...>, list<L0x0BC...>, list<L0x0BD...>, list<L0x0BE...>, list<L0x0BF...>
                , list<L0x0C0...>, list<L0x0C1...>, list<L0x0C2...>, list<L0x0C3...>, list<L0x0C4...>, list<L0x0C5...>, list<L0x0C6...>, list<L0x0C7...>, list<L0x0C8...>, list<L0x0C9...>, list<L0x0CA...>, list<L0x0CB...>, list<L0x0CC...>, list<L0x0CD...>, list<L0x0CE...>, list<L0x0CF...>
                , list<L0x0D0...>, list<L0x0D1...>, list<L0x0D2...>, list<L0x0D3...>, list<L0x0D4...>, list<L0x0D5...>, list<L0x0D6...>, list<L0x0D7...>, list<L0x0D8...>, list<L0x0D9...>, list<L0x0DA...>, list<L0x0DB...>, list<L0x0DC...>, list<L0x0DD...>, list<L0x0DE...>, list<L0x0DF...>
                , list<L0x0E0...>, list<L0x0E1...>, list<L0x0E2...>, list<L0x0E3...>, list<L0x0E4...>, list<L0x0E5...>, list<L0x0E6...>, list<L0x0E7...>, list<L0x0E8...>, list<L0x0E9...>, list<L0x0EA...>, list<L0x0EB...>, list<L0x0EC...>, list<L0x0ED...>, list<L0x0EE...>, list<L0x0EF...>
                , list<L0x0F0...>, list<L0x0F1...>, list<L0x0F2...>, list<L0x0F3...>, list<L0x0F4...>, list<L0x0F5...>, list<L0x0F6...>, list<L0x0F7...>, list<L0x0F8...>, list<L0x0F9...>, list<L0x0FA...>, list<L0x0FB...>, list<L0x0FC...>, list<L0x0FD...>, list<L0x0FE...>, list<L0x0FF...>

                , list<L0x100...>, list<L0x101...>, list<L0x102...>, list<L0x103...>, list<L0x104...>, list<L0x105...>, list<L0x106...>, list<L0x107...>, list<L0x108...>, list<L0x109...>, list<L0x10A...>, list<L0x10B...>, list<L0x10C...>, list<L0x10D...>, list<L0x10E...>, list<L0x10F...>
                , list<L0x110...>, list<L0x111...>, list<L0x112...>, list<L0x113...>, list<L0x114...>, list<L0x115...>, list<L0x116...>, list<L0x117...>, list<L0x118...>, list<L0x119...>, list<L0x11A...>, list<L0x11B...>, list<L0x11C...>, list<L0x11D...>, list<L0x11E...>, list<L0x11F...>
                , list<L0x120...>, list<L0x121...>, list<L0x122...>, list<L0x123...>, list<L0x124...>, list<L0x125...>, list<L0x126...>, list<L0x127...>, list<L0x128...>, list<L0x129...>, list<L0x12A...>, list<L0x12B...>, list<L0x12C...>, list<L0x12D...>, list<L0x12E...>, list<L0x12F...>
                , list<L0x130...>, list<L0x131...>, list<L0x132...>, list<L0x133...>, list<L0x134...>, list<L0x135...>, list<L0x136...>, list<L0x137...>, list<L0x138...>, list<L0x139...>, list<L0x13A...>, list<L0x13B...>, list<L0x13C...>, list<L0x13D...>, list<L0x13E...>, list<L0x13F...>
                , list<L0x140...>, list<L0x141...>, list<L0x142...>, list<L0x143...>, list<L0x144...>, list<L0x145...>, list<L0x146...>, list<L0x147...>, list<L0x148...>, list<L0x149...>, list<L0x14A...>, list<L0x14B...>, list<L0x14C...>, list<L0x14D...>, list<L0x14E...>, list<L0x14F...>
                , list<L0x150...>, list<L0x151...>, list<L0x152...>, list<L0x153...>, list<L0x154...>, list<L0x155...>, list<L0x156...>, list<L0x157...>, list<L0x158...>, list<L0x159...>, list<L0x15A...>, list<L0x15B...>, list<L0x15C...>, list<L0x15D...>, list<L0x15E...>, list<L0x15F...>
                , list<L0x160...>, list<L0x161...>, list<L0x162...>, list<L0x163...>, list<L0x164...>, list<L0x165...>, list<L0x166...>, list<L0x167...>, list<L0x168...>, list<L0x169...>, list<L0x16A...>, list<L0x16B...>, list<L0x16C...>, list<L0x16D...>, list<L0x16E...>, list<L0x16F...>
                , list<L0x170...>, list<L0x171...>, list<L0x172...>, list<L0x173...>, list<L0x174...>, list<L0x175...>, list<L0x176...>, list<L0x177...>, list<L0x178...>, list<L0x179...>, list<L0x17A...>, list<L0x17B...>, list<L0x17C...>, list<L0x17D...>, list<L0x17E...>, list<L0x17F...>
                , list<L0x180...>, list<L0x181...>, list<L0x182...>, list<L0x183...>, list<L0x184...>, list<L0x185...>, list<L0x186...>, list<L0x187...>, list<L0x188...>, list<L0x189...>, list<L0x18A...>, list<L0x18B...>, list<L0x18C...>, list<L0x18D...>, list<L0x18E...>, list<L0x18F...>
                , list<L0x190...>, list<L0x191...>, list<L0x192...>, list<L0x193...>, list<L0x194...>, list<L0x195...>, list<L0x196...>, list<L0x197...>, list<L0x198...>, list<L0x199...>, list<L0x19A...>, list<L0x19B...>, list<L0x19C...>, list<L0x19D...>, list<L0x19E...>, list<L0x19F...>
                , list<L0x1A0...>, list<L0x1A1...>, list<L0x1A2...>, list<L0x1A3...>, list<L0x1A4...>, list<L0x1A5...>, list<L0x1A6...>, list<L0x1A7...>, list<L0x1A8...>, list<L0x1A9...>, list<L0x1AA...>, list<L0x1AB...>, list<L0x1AC...>, list<L0x1AD...>, list<L0x1AE...>, list<L0x1AF...>
                , list<L0x1B0...>, list<L0x1B1...>, list<L0x1B2...>, list<L0x1B3...>, list<L0x1B4...>, list<L0x1B5...>, list<L0x1B6...>, list<L0x1B7...>, list<L0x1B8...>, list<L0x1B9...>, list<L0x1BA...>, list<L0x1BB...>, list<L0x1BC...>, list<L0x1BD...>, list<L0x1BE...>, list<L0x1BF...>
                , list<L0x1C0...>, list<L0x1C1...>, list<L0x1C2...>, list<L0x1C3...>, list<L0x1C4...>, list<L0x1C5...>, list<L0x1C6...>, list<L0x1C7...>, list<L0x1C8...>, list<L0x1C9...>, list<L0x1CA...>, list<L0x1CB...>, list<L0x1CC...>, list<L0x1CD...>, list<L0x1CE...>, list<L0x1CF...>
                , list<L0x1D0...>, list<L0x1D1...>, list<L0x1D2...>, list<L0x1D3...>, list<L0x1D4...>, list<L0x1D5...>, list<L0x1D6...>, list<L0x1D7...>, list<L0x1D8...>, list<L0x1D9...>, list<L0x1DA...>, list<L0x1DB...>, list<L0x1DC...>, list<L0x1DD...>, list<L0x1DE...>, list<L0x1DF...>
                , list<L0x1E0...>, list<L0x1E1...>, list<L0x1E2...>, list<L0x1E3...>, list<L0x1E4...>, list<L0x1E5...>, list<L0x1E6...>, list<L0x1E7...>, list<L0x1E8...>, list<L0x1E9...>, list<L0x1EA...>, list<L0x1EB...>, list<L0x1EC...>, list<L0x1ED...>, list<L0x1EE...>, list<L0x1EF...>
                , list<L0x1F0...>, list<L0x1F1...>, list<L0x1F2...>, list<L0x1F3...>, list<L0x1F4...>, list<L0x1F5...>, list<L0x1F6...>, list<L0x1F7...>, list<L0x1F8...>, list<L0x1F9...>, list<L0x1FA...>, list<L0x1FB...>, list<L0x1FC...>, list<L0x1FD...>, list<L0x1FE...>, list<L0x1FF...>

                , list<L0x200...>, list<L0x201...>, list<L0x202...>, list<L0x203...>, list<L0x204...>, list<L0x205...>, list<L0x206...>, list<L0x207...>, list<L0x208...>, list<L0x209...>, list<L0x20A...>, list<L0x20B...>, list<L0x20C...>, list<L0x20D...>, list<L0x20E...>, list<L0x20F...>
                , list<L0x210...>, list<L0x211...>, list<L0x212...>, list<L0x213...>, list<L0x214...>, list<L0x215...>, list<L0x216...>, list<L0x217...>, list<L0x218...>, list<L0x219...>, list<L0x21A...>, list<L0x21B...>, list<L0x21C...>, list<L0x21D...>, list<L0x21E...>, list<L0x21F...>
                , list<L0x220...>, list<L0x221...>, list<L0x222...>, list<L0x223...>, list<L0x224...>, list<L0x225...>, list<L0x226...>, list<L0x227...>, list<L0x228...>, list<L0x229...>, list<L0x22A...>, list<L0x22B...>, list<L0x22C...>, list<L0x22D...>, list<L0x22E...>, list<L0x22F...>
                , list<L0x230...>, list<L0x231...>, list<L0x232...>, list<L0x233...>, list<L0x234...>, list<L0x235...>, list<L0x236...>, list<L0x237...>, list<L0x238...>, list<L0x239...>, list<L0x23A...>, list<L0x23B...>, list<L0x23C...>, list<L0x23D...>, list<L0x23E...>, list<L0x23F...>
                , list<L0x240...>, list<L0x241...>, list<L0x242...>, list<L0x243...>, list<L0x244...>, list<L0x245...>, list<L0x246...>, list<L0x247...>, list<L0x248...>, list<L0x249...>, list<L0x24A...>, list<L0x24B...>, list<L0x24C...>, list<L0x24D...>, list<L0x24E...>, list<L0x24F...>
                , list<L0x250...>, list<L0x251...>, list<L0x252...>, list<L0x253...>, list<L0x254...>, list<L0x255...>, list<L0x256...>, list<L0x257...>, list<L0x258...>, list<L0x259...>, list<L0x25A...>, list<L0x25B...>, list<L0x25C...>, list<L0x25D...>, list<L0x25E...>, list<L0x25F...>
                , list<L0x260...>, list<L0x261...>, list<L0x262...>, list<L0x263...>, list<L0x264...>, list<L0x265...>, list<L0x266...>, list<L0x267...>, list<L0x268...>, list<L0x269...>, list<L0x26A...>, list<L0x26B...>, list<L0x26C...>, list<L0x26D...>, list<L0x26E...>, list<L0x26F...>
                , list<L0x270...>, list<L0x271...>, list<L0x272...>, list<L0x273...>, list<L0x274...>, list<L0x275...>, list<L0x276...>, list<L0x277...>, list<L0x278...>, list<L0x279...>, list<L0x27A...>, list<L0x27B...>, list<L0x27C...>, list<L0x27D...>, list<L0x27E...>, list<L0x27F...>
                , list<L0x280...>, list<L0x281...>, list<L0x282...>, list<L0x283...>, list<L0x284...>, list<L0x285...>, list<L0x286...>, list<L0x287...>, list<L0x288...>, list<L0x289...>, list<L0x28A...>, list<L0x28B...>, list<L0x28C...>, list<L0x28D...>, list<L0x28E...>, list<L0x28F...>
                , list<L0x290...>, list<L0x291...>, list<L0x292...>, list<L0x293...>, list<L0x294...>, list<L0x295...>, list<L0x296...>, list<L0x297...>, list<L0x298...>, list<L0x299...>, list<L0x29A...>, list<L0x29B...>, list<L0x29C...>, list<L0x29D...>, list<L0x29E...>, list<L0x29F...>
                , list<L0x2A0...>, list<L0x2A1...>, list<L0x2A2...>, list<L0x2A3...>, list<L0x2A4...>, list<L0x2A5...>, list<L0x2A6...>, list<L0x2A7...>, list<L0x2A8...>, list<L0x2A9...>, list<L0x2AA...>, list<L0x2AB...>, list<L0x2AC...>, list<L0x2AD...>, list<L0x2AE...>, list<L0x2AF...>
                , list<L0x2B0...>, list<L0x2B1...>, list<L0x2B2...>, list<L0x2B3...>, list<L0x2B4...>, list<L0x2B5...>, list<L0x2B6...>, list<L0x2B7...>, list<L0x2B8...>, list<L0x2B9...>, list<L0x2BA...>, list<L0x2BB...>, list<L0x2BC...>, list<L0x2BD...>, list<L0x2BE...>, list<L0x2BF...>
                , list<L0x2C0...>, list<L0x2C1...>, list<L0x2C2...>, list<L0x2C3...>, list<L0x2C4...>, list<L0x2C5...>, list<L0x2C6...>, list<L0x2C7...>, list<L0x2C8...>, list<L0x2C9...>, list<L0x2CA...>, list<L0x2CB...>, list<L0x2CC...>, list<L0x2CD...>, list<L0x2CE...>, list<L0x2CF...>
                , list<L0x2D0...>, list<L0x2D1...>, list<L0x2D2...>, list<L0x2D3...>, list<L0x2D4...>, list<L0x2D5...>, list<L0x2D6...>, list<L0x2D7...>, list<L0x2D8...>, list<L0x2D9...>, list<L0x2DA...>, list<L0x2DB...>, list<L0x2DC...>, list<L0x2DD...>, list<L0x2DE...>, list<L0x2DF...>
                , list<L0x2E0...>, list<L0x2E1...>, list<L0x2E2...>, list<L0x2E3...>, list<L0x2E4...>, list<L0x2E5...>, list<L0x2E6...>, list<L0x2E7...>, list<L0x2E8...>, list<L0x2E9...>, list<L0x2EA...>, list<L0x2EB...>, list<L0x2EC...>, list<L0x2ED...>, list<L0x2EE...>, list<L0x2EF...>
                , list<L0x2F0...>, list<L0x2F1...>, list<L0x2F2...>, list<L0x2F3...>, list<L0x2F4...>, list<L0x2F5...>, list<L0x2F6...>, list<L0x2F7...>, list<L0x2F8...>, list<L0x2F9...>, list<L0x2FA...>, list<L0x2FB...>, list<L0x2FC...>, list<L0x2FD...>, list<L0x2FE...>, list<L0x2FF...>

                , list<L0x300...>, list<L0x301...>, list<L0x302...>, list<L0x303...>, list<L0x304...>, list<L0x305...>, list<L0x306...>, list<L0x307...>, list<L0x308...>, list<L0x309...>, list<L0x30A...>, list<L0x30B...>, list<L0x30C...>, list<L0x30D...>, list<L0x30E...>, list<L0x30F...>
                , list<L0x310...>, list<L0x311...>, list<L0x312...>, list<L0x313...>, list<L0x314...>, list<L0x315...>, list<L0x316...>, list<L0x317...>, list<L0x318...>, list<L0x319...>, list<L0x31A...>, list<L0x31B...>, list<L0x31C...>, list<L0x31D...>, list<L0x31E...>, list<L0x31F...>
                , list<L0x320...>, list<L0x321...>, list<L0x322...>, list<L0x323...>, list<L0x324...>, list<L0x325...>, list<L0x326...>, list<L0x327...>, list<L0x328...>, list<L0x329...>, list<L0x32A...>, list<L0x32B...>, list<L0x32C...>, list<L0x32D...>, list<L0x32E...>, list<L0x32F...>
                , list<L0x330...>, list<L0x331...>, list<L0x332...>, list<L0x333...>, list<L0x334...>, list<L0x335...>, list<L0x336...>, list<L0x337...>, list<L0x338...>, list<L0x339...>, list<L0x33A...>, list<L0x33B...>, list<L0x33C...>, list<L0x33D...>, list<L0x33E...>, list<L0x33F...>
                , list<L0x340...>, list<L0x341...>, list<L0x342...>, list<L0x343...>, list<L0x344...>, list<L0x345...>, list<L0x346...>, list<L0x347...>, list<L0x348...>, list<L0x349...>, list<L0x34A...>, list<L0x34B...>, list<L0x34C...>, list<L0x34D...>, list<L0x34E...>, list<L0x34F...>
                , list<L0x350...>, list<L0x351...>, list<L0x352...>, list<L0x353...>, list<L0x354...>, list<L0x355...>, list<L0x356...>, list<L0x357...>, list<L0x358...>, list<L0x359...>, list<L0x35A...>, list<L0x35B...>, list<L0x35C...>, list<L0x35D...>, list<L0x35E...>, list<L0x35F...>
                , list<L0x360...>, list<L0x361...>, list<L0x362...>, list<L0x363...>, list<L0x364...>, list<L0x365...>, list<L0x366...>, list<L0x367...>, list<L0x368...>, list<L0x369...>, list<L0x36A...>, list<L0x36B...>, list<L0x36C...>, list<L0x36D...>, list<L0x36E...>, list<L0x36F...>
                , list<L0x370...>, list<L0x371...>, list<L0x372...>, list<L0x373...>, list<L0x374...>, list<L0x375...>, list<L0x376...>, list<L0x377...>, list<L0x378...>, list<L0x379...>, list<L0x37A...>, list<L0x37B...>, list<L0x37C...>, list<L0x37D...>, list<L0x37E...>, list<L0x37F...>
                , list<L0x380...>, list<L0x381...>, list<L0x382...>, list<L0x383...>, list<L0x384...>, list<L0x385...>, list<L0x386...>, list<L0x387...>, list<L0x388...>, list<L0x389...>, list<L0x38A...>, list<L0x38B...>, list<L0x38C...>, list<L0x38D...>, list<L0x38E...>, list<L0x38F...>
                , list<L0x390...>, list<L0x391...>, list<L0x392...>, list<L0x393...>, list<L0x394...>, list<L0x395...>, list<L0x396...>, list<L0x397...>, list<L0x398...>, list<L0x399...>, list<L0x39A...>, list<L0x39B...>, list<L0x39C...>, list<L0x39D...>, list<L0x39E...>, list<L0x39F...>
                , list<L0x3A0...>, list<L0x3A1...>, list<L0x3A2...>, list<L0x3A3...>, list<L0x3A4...>, list<L0x3A5...>, list<L0x3A6...>, list<L0x3A7...>, list<L0x3A8...>, list<L0x3A9...>, list<L0x3AA...>, list<L0x3AB...>, list<L0x3AC...>, list<L0x3AD...>, list<L0x3AE...>, list<L0x3AF...>
                , list<L0x3B0...>, list<L0x3B1...>, list<L0x3B2...>, list<L0x3B3...>, list<L0x3B4...>, list<L0x3B5...>, list<L0x3B6...>, list<L0x3B7...>, list<L0x3B8...>, list<L0x3B9...>, list<L0x3BA...>, list<L0x3BB...>, list<L0x3BC...>, list<L0x3BD...>, list<L0x3BE...>, list<L0x3BF...>
                , list<L0x3C0...>, list<L0x3C1...>, list<L0x3C2...>, list<L0x3C3...>, list<L0x3C4...>, list<L0x3C5...>, list<L0x3C6...>, list<L0x3C7...>, list<L0x3C8...>, list<L0x3C9...>, list<L0x3CA...>, list<L0x3CB...>, list<L0x3CC...>, list<L0x3CD...>, list<L0x3CE...>, list<L0x3CF...>
                , list<L0x3D0...>, list<L0x3D1...>, list<L0x3D2...>, list<L0x3D3...>, list<L0x3D4...>, list<L0x3D5...>, list<L0x3D6...>, list<L0x3D7...>, list<L0x3D8...>, list<L0x3D9...>, list<L0x3DA...>, list<L0x3DB...>, list<L0x3DC...>, list<L0x3DD...>, list<L0x3DE...>, list<L0x3DF...>
                , list<L0x3E0...>, list<L0x3E1...>, list<L0x3E2...>, list<L0x3E3...>, list<L0x3E4...>, list<L0x3E5...>, list<L0x3E6...>, list<L0x3E7...>, list<L0x3E8...>, list<L0x3E9...>, list<L0x3EA...>, list<L0x3EB...>, list<L0x3EC...>, list<L0x3ED...>, list<L0x3EE...>, list<L0x3EF...>
                , list<L0x3F0...>, list<L0x3F1...>, list<L0x3F2...>, list<L0x3F3...>, list<L0x3F4...>, list<L0x3F5...>, list<L0x3F6...>, list<L0x3F7...>, list<L0x3F8...>, list<L0x3F9...>, list<L0x3FA...>, list<L0x3FB...>, list<L0x3FC...>, list<L0x3FD...>, list<L0x3FE...>, list<L0x3FF...>
            >
            {
                template<typename C>
                using f =
                    typename C::template f<
                          L0x000..., L0x001..., L0x002..., L0x003..., L0x004..., L0x005..., L0x006..., L0x007..., L0x008..., L0x009..., L0x00A..., L0x00B..., L0x00C..., L0x00D..., L0x00E..., L0x00F...
                        , L0x010..., L0x011..., L0x012..., L0x013..., L0x014..., L0x015..., L0x016..., L0x017..., L0x018..., L0x019..., L0x01A..., L0x01B..., L0x01C..., L0x01D..., L0x01E..., L0x01F...
                        , L0x020..., L0x021..., L0x022..., L0x023..., L0x024..., L0x025..., L0x026..., L0x027..., L0x028..., L0x029..., L0x02A..., L0x02B..., L0x02C..., L0x02D..., L0x02E..., L0x02F...
                        , L0x030..., L0x031..., L0x032..., L0x033..., L0x034..., L0x035..., L0x036..., L0x037..., L0x038..., L0x039..., L0x03A..., L0x03B..., L0x03C..., L0x03D..., L0x03E..., L0x03F...
                        , L0x040..., L0x041..., L0x042..., L0x043..., L0x044..., L0x045..., L0x046..., L0x047..., L0x048..., L0x049..., L0x04A..., L0x04B..., L0x04C..., L0x04D..., L0x04E..., L0x04F...
                        , L0x050..., L0x051..., L0x052..., L0x053..., L0x054..., L0x055..., L0x056..., L0x057..., L0x058..., L0x059..., L0x05A..., L0x05B..., L0x05C..., L0x05D..., L0x05E..., L0x05F...
                        , L0x060..., L0x061..., L0x062..., L0x063..., L0x064..., L0x065..., L0x066..., L0x067..., L0x068..., L0x069..., L0x06A..., L0x06B..., L0x06C..., L0x06D..., L0x06E..., L0x06F...
                        , L0x070..., L0x071..., L0x072..., L0x073..., L0x074..., L0x075..., L0x076..., L0x077..., L0x078..., L0x079..., L0x07A..., L0x07B..., L0x07C..., L0x07D..., L0x07E..., L0x07F...
                        , L0x080..., L0x081..., L0x082..., L0x083..., L0x084..., L0x085..., L0x086..., L0x087..., L0x088..., L0x089..., L0x08A..., L0x08B..., L0x08C..., L0x08D..., L0x08E..., L0x08F...
                        , L0x090..., L0x091..., L0x092..., L0x093..., L0x094..., L0x095..., L0x096..., L0x097..., L0x098..., L0x099..., L0x09A..., L0x09B..., L0x09C..., L0x09D..., L0x09E..., L0x09F...
                        , L0x0A0..., L0x0A1..., L0x0A2..., L0x0A3..., L0x0A4..., L0x0A5..., L0x0A6..., L0x0A7..., L0x0A8..., L0x0A9..., L0x0AA..., L0x0AB..., L0x0AC..., L0x0AD..., L0x0AE..., L0x0AF...
                        , L0x0B0..., L0x0B1..., L0x0B2..., L0x0B3..., L0x0B4..., L0x0B5..., L0x0B6..., L0x0B7..., L0x0B8..., L0x0B9..., L0x0BA..., L0x0BB..., L0x0BC..., L0x0BD..., L0x0BE..., L0x0BF...
                        , L0x0C0..., L0x0C1..., L0x0C2..., L0x0C3..., L0x0C4..., L0x0C5..., L0x0C6..., L0x0C7..., L0x0C8..., L0x0C9..., L0x0CA..., L0x0CB..., L0x0CC..., L0x0CD..., L0x0CE..., L0x0CF...
                        , L0x0D0..., L0x0D1..., L0x0D2..., L0x0D3..., L0x0D4..., L0x0D5..., L0x0D6..., L0x0D7..., L0x0D8..., L0x0D9..., L0x0DA..., L0x0DB..., L0x0DC..., L0x0DD..., L0x0DE..., L0x0DF...
                        , L0x0E0..., L0x0E1..., L0x0E2..., L0x0E3..., L0x0E4..., L0x0E5..., L0x0E6..., L0x0E7..., L0x0E8..., L0x0E9..., L0x0EA..., L0x0EB..., L0x0EC..., L0x0ED..., L0x0EE..., L0x0EF...
                        , L0x0F0..., L0x0F1..., L0x0F2..., L0x0F3..., L0x0F4..., L0x0F5..., L0x0F6..., L0x0F7..., L0x0F8..., L0x0F9..., L0x0FA..., L0x0FB..., L0x0FC..., L0x0FD..., L0x0FE..., L0x0FF...
                        
                        , L0x100..., L0x101..., L0x102..., L0x103..., L0x104..., L0x105..., L0x106..., L0x107..., L0x108..., L0x109..., L0x10A..., L0x10B..., L0x10C..., L0x10D..., L0x10E..., L0x10F...
                        , L0x110..., L0x111..., L0x112..., L0x113..., L0x114..., L0x115..., L0x116..., L0x117..., L0x118..., L0x119..., L0x11A..., L0x11B..., L0x11C..., L0x11D..., L0x11E..., L0x11F...
                        , L0x120..., L0x121..., L0x122..., L0x123..., L0x124..., L0x125..., L0x126..., L0x127..., L0x128..., L0x129..., L0x12A..., L0x12B..., L0x12C..., L0x12D..., L0x12E..., L0x12F...
                        , L0x130..., L0x131..., L0x132..., L0x133..., L0x134..., L0x135..., L0x136..., L0x137..., L0x138..., L0x139..., L0x13A..., L0x13B..., L0x13C..., L0x13D..., L0x13E..., L0x13F...
                        , L0x140..., L0x141..., L0x142..., L0x143..., L0x144..., L0x145..., L0x146..., L0x147..., L0x148..., L0x149..., L0x14A..., L0x14B..., L0x14C..., L0x14D..., L0x14E..., L0x14F...
                        , L0x150..., L0x151..., L0x152..., L0x153..., L0x154..., L0x155..., L0x156..., L0x157..., L0x158..., L0x159..., L0x15A..., L0x15B..., L0x15C..., L0x15D..., L0x15E..., L0x15F...
                        , L0x160..., L0x161..., L0x162..., L0x163..., L0x164..., L0x165..., L0x166..., L0x167..., L0x168..., L0x169..., L0x16A..., L0x16B..., L0x16C..., L0x16D..., L0x16E..., L0x16F...
                        , L0x170..., L0x171..., L0x172..., L0x173..., L0x174..., L0x175..., L0x176..., L0x177..., L0x178..., L0x179..., L0x17A..., L0x17B..., L0x17C..., L0x17D..., L0x17E..., L0x17F...
                        , L0x180..., L0x181..., L0x182..., L0x183..., L0x184..., L0x185..., L0x186..., L0x187..., L0x188..., L0x189..., L0x18A..., L0x18B..., L0x18C..., L0x18D..., L0x18E..., L0x18F...
                        , L0x190..., L0x191..., L0x192..., L0x193..., L0x194..., L0x195..., L0x196..., L0x197..., L0x198..., L0x199..., L0x19A..., L0x19B..., L0x19C..., L0x19D..., L0x19E..., L0x19F...
                        , L0x1A0..., L0x1A1..., L0x1A2..., L0x1A3..., L0x1A4..., L0x1A5..., L0x1A6..., L0x1A7..., L0x1A8..., L0x1A9..., L0x1AA..., L0x1AB..., L0x1AC..., L0x1AD..., L0x1AE..., L0x1AF...
                        , L0x1B0..., L0x1B1..., L0x1B2..., L0x1B3..., L0x1B4..., L0x1B5..., L0x1B6..., L0x1B7..., L0x1B8..., L0x1B9..., L0x1BA..., L0x1BB..., L0x1BC..., L0x1BD..., L0x1BE..., L0x1BF...
                        , L0x1C0..., L0x1C1..., L0x1C2..., L0x1C3..., L0x1C4..., L0x1C5..., L0x1C6..., L0x1C7..., L0x1C8..., L0x1C9..., L0x1CA..., L0x1CB..., L0x1CC..., L0x1CD..., L0x1CE..., L0x1CF...
                        , L0x1D0..., L0x1D1..., L0x1D2..., L0x1D3..., L0x1D4..., L0x1D5..., L0x1D6..., L0x1D7..., L0x1D8..., L0x1D9..., L0x1DA..., L0x1DB..., L0x1DC..., L0x1DD..., L0x1DE..., L0x1DF...
                        , L0x1E0..., L0x1E1..., L0x1E2..., L0x1E3..., L0x1E4..., L0x1E5..., L0x1E6..., L0x1E7..., L0x1E8..., L0x1E9..., L0x1EA..., L0x1EB..., L0x1EC..., L0x1ED..., L0x1EE..., L0x1EF...
                        , L0x1F0..., L0x1F1..., L0x1F2..., L0x1F3..., L0x1F4..., L0x1F5..., L0x1F6..., L0x1F7..., L0x1F8..., L0x1F9..., L0x1FA..., L0x1FB..., L0x1FC..., L0x1FD..., L0x1FE..., L0x1FF...
                        
                        , L0x200..., L0x201..., L0x202..., L0x203..., L0x204..., L0x205..., L0x206..., L0x207..., L0x208..., L0x209..., L0x20A..., L0x20B..., L0x20C..., L0x20D..., L0x20E..., L0x20F...
                        , L0x210..., L0x211..., L0x212..., L0x213..., L0x214..., L0x215..., L0x216..., L0x217..., L0x218..., L0x219..., L0x21A..., L0x21B..., L0x21C..., L0x21D..., L0x21E..., L0x21F...
                        , L0x220..., L0x221..., L0x222..., L0x223..., L0x224..., L0x225..., L0x226..., L0x227..., L0x228..., L0x229..., L0x22A..., L0x22B..., L0x22C..., L0x22D..., L0x22E..., L0x22F...
                        , L0x230..., L0x231..., L0x232..., L0x233..., L0x234..., L0x235..., L0x236..., L0x237..., L0x238..., L0x239..., L0x23A..., L0x23B..., L0x23C..., L0x23D..., L0x23E..., L0x23F...
                        , L0x240..., L0x241..., L0x242..., L0x243..., L0x244..., L0x245..., L0x246..., L0x247..., L0x248..., L0x249..., L0x24A..., L0x24B..., L0x24C..., L0x24D..., L0x24E..., L0x24F...
                        , L0x250..., L0x251..., L0x252..., L0x253..., L0x254..., L0x255..., L0x256..., L0x257..., L0x258..., L0x259..., L0x25A..., L0x25B..., L0x25C..., L0x25D..., L0x25E..., L0x25F...
                        , L0x260..., L0x261..., L0x262..., L0x263..., L0x264..., L0x265..., L0x266..., L0x267..., L0x268..., L0x269..., L0x26A..., L0x26B..., L0x26C..., L0x26D..., L0x26E..., L0x26F...
                        , L0x270..., L0x271..., L0x272..., L0x273..., L0x274..., L0x275..., L0x276..., L0x277..., L0x278..., L0x279..., L0x27A..., L0x27B..., L0x27C..., L0x27D..., L0x27E..., L0x27F...
                        , L0x280..., L0x281..., L0x282..., L0x283..., L0x284..., L0x285..., L0x286..., L0x287..., L0x288..., L0x289..., L0x28A..., L0x28B..., L0x28C..., L0x28D..., L0x28E..., L0x28F...
                        , L0x290..., L0x291..., L0x292..., L0x293..., L0x294..., L0x295..., L0x296..., L0x297..., L0x298..., L0x299..., L0x29A..., L0x29B..., L0x29C..., L0x29D..., L0x29E..., L0x29F...
                        , L0x2A0..., L0x2A1..., L0x2A2..., L0x2A3..., L0x2A4..., L0x2A5..., L0x2A6..., L0x2A7..., L0x2A8..., L0x2A9..., L0x2AA..., L0x2AB..., L0x2AC..., L0x2AD..., L0x2AE..., L0x2AF...
                        , L0x2B0..., L0x2B1..., L0x2B2..., L0x2B3..., L0x2B4..., L0x2B5..., L0x2B6..., L0x2B7..., L0x2B8..., L0x2B9..., L0x2BA..., L0x2BB..., L0x2BC..., L0x2BD..., L0x2BE..., L0x2BF...
                        , L0x2C0..., L0x2C1..., L0x2C2..., L0x2C3..., L0x2C4..., L0x2C5..., L0x2C6..., L0x2C7..., L0x2C8..., L0x2C9..., L0x2CA..., L0x2CB..., L0x2CC..., L0x2CD..., L0x2CE..., L0x2CF...
                        , L0x2D0..., L0x2D1..., L0x2D2..., L0x2D3..., L0x2D4..., L0x2D5..., L0x2D6..., L0x2D7..., L0x2D8..., L0x2D9..., L0x2DA..., L0x2DB..., L0x2DC..., L0x2DD..., L0x2DE..., L0x2DF...
                        , L0x2E0..., L0x2E1..., L0x2E2..., L0x2E3..., L0x2E4..., L0x2E5..., L0x2E6..., L0x2E7..., L0x2E8..., L0x2E9..., L0x2EA..., L0x2EB..., L0x2EC..., L0x2ED..., L0x2EE..., L0x2EF...
                        , L0x2F0..., L0x2F1..., L0x2F2..., L0x2F3..., L0x2F4..., L0x2F5..., L0x2F6..., L0x2F7..., L0x2F8..., L0x2F9..., L0x2FA..., L0x2FB..., L0x2FC..., L0x2FD..., L0x2FE..., L0x2FF...
                        
                        , L0x300..., L0x301..., L0x302..., L0x303..., L0x304..., L0x305..., L0x306..., L0x307..., L0x308..., L0x309..., L0x30A..., L0x30B..., L0x30C..., L0x30D..., L0x30E..., L0x30F...
                        , L0x310..., L0x311..., L0x312..., L0x313..., L0x314..., L0x315..., L0x316..., L0x317..., L0x318..., L0x319..., L0x31A..., L0x31B..., L0x31C..., L0x31D..., L0x31E..., L0x31F...
                        , L0x320..., L0x321..., L0x322..., L0x323..., L0x324..., L0x325..., L0x326..., L0x327..., L0x328..., L0x329..., L0x32A..., L0x32B..., L0x32C..., L0x32D..., L0x32E..., L0x32F...
                        , L0x330..., L0x331..., L0x332..., L0x333..., L0x334..., L0x335..., L0x336..., L0x337..., L0x338..., L0x339..., L0x33A..., L0x33B..., L0x33C..., L0x33D..., L0x33E..., L0x33F...
                        , L0x340..., L0x341..., L0x342..., L0x343..., L0x344..., L0x345..., L0x346..., L0x347..., L0x348..., L0x349..., L0x34A..., L0x34B..., L0x34C..., L0x34D..., L0x34E..., L0x34F...
                        , L0x350..., L0x351..., L0x352..., L0x353..., L0x354..., L0x355..., L0x356..., L0x357..., L0x358..., L0x359..., L0x35A..., L0x35B..., L0x35C..., L0x35D..., L0x35E..., L0x35F...
                        , L0x360..., L0x361..., L0x362..., L0x363..., L0x364..., L0x365..., L0x366..., L0x367..., L0x368..., L0x369..., L0x36A..., L0x36B..., L0x36C..., L0x36D..., L0x36E..., L0x36F...
                        , L0x370..., L0x371..., L0x372..., L0x373..., L0x374..., L0x375..., L0x376..., L0x377..., L0x378..., L0x379..., L0x37A..., L0x37B..., L0x37C..., L0x37D..., L0x37E..., L0x37F...
                        , L0x380..., L0x381..., L0x382..., L0x383..., L0x384..., L0x385..., L0x386..., L0x387..., L0x388..., L0x389..., L0x38A..., L0x38B..., L0x38C..., L0x38D..., L0x38E..., L0x38F...
                        , L0x390..., L0x391..., L0x392..., L0x393..., L0x394..., L0x395..., L0x396..., L0x397..., L0x398..., L0x399..., L0x39A..., L0x39B..., L0x39C..., L0x39D..., L0x39E..., L0x39F...
                        , L0x3A0..., L0x3A1..., L0x3A2..., L0x3A3..., L0x3A4..., L0x3A5..., L0x3A6..., L0x3A7..., L0x3A8..., L0x3A9..., L0x3AA..., L0x3AB..., L0x3AC..., L0x3AD..., L0x3AE..., L0x3AF...
                        , L0x3B0..., L0x3B1..., L0x3B2..., L0x3B3..., L0x3B4..., L0x3B5..., L0x3B6..., L0x3B7..., L0x3B8..., L0x3B9..., L0x3BA..., L0x3BB..., L0x3BC..., L0x3BD..., L0x3BE..., L0x3BF...
                        , L0x3C0..., L0x3C1..., L0x3C2..., L0x3C3..., L0x3C4..., L0x3C5..., L0x3C6..., L0x3C7..., L0x3C8..., L0x3C9..., L0x3CA..., L0x3CB..., L0x3CC..., L0x3CD..., L0x3CE..., L0x3CF...
                        , L0x3D0..., L0x3D1..., L0x3D2..., L0x3D3..., L0x3D4..., L0x3D5..., L0x3D6..., L0x3D7..., L0x3D8..., L0x3D9..., L0x3DA..., L0x3DB..., L0x3DC..., L0x3DD..., L0x3DE..., L0x3DF...
                        , L0x3E0..., L0x3E1..., L0x3E2..., L0x3E3..., L0x3E4..., L0x3E5..., L0x3E6..., L0x3E7..., L0x3E8..., L0x3E9..., L0x3EA..., L0x3EB..., L0x3EC..., L0x3ED..., L0x3EE..., L0x3EF...
                        , L0x3F0..., L0x3F1..., L0x3F2..., L0x3F3..., L0x3F4..., L0x3F5..., L0x3F6..., L0x3F7..., L0x3F8..., L0x3F9..., L0x3FA..., L0x3FB..., L0x3FC..., L0x3FD..., L0x3FE..., L0x3FF...
                    >;
            };
        };
    }
    
    struct join 
    {
        template<typename C, typename... Lists>
        using continuation = deferred_call_f<detail::join_impl<detail::selectJoinSize(sizeof...(Lists))>::template split<Lists...>::template f, C>;
    };
}
}

