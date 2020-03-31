/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once

/* Main header/source */
#define HEADER_STREAM_PTR() (param.getHeaderStream())
#define HEADER_STREAM() (*HEADER_STREAM_PTR())
#define HEADER(__action)               \
    do                                 \
    {                                  \
        (HEADER_STREAM()) << __action; \
    } while (0);
#define SOURCE_STREAM_PTR() (param.getSourceStream())
#define SOURCE_STREAM() (*SOURCE_STREAM_PTR())
#define SOURCE(__action)               \
    do                                 \
    {                                  \
        (SOURCE_STREAM()) << __action; \
    } while (0);
#define BOTH(__action)   \
    do                   \
    {                    \
        HEADER(__action) \
        SOURCE(__action) \
    } while (0);

/* Operation header/source streams */
#define HEADER_OP_STREAM_PTR() (param.getHeaderOpStream())
#define HEADER_OP_STREAM() (*HEADER_OP_STREAM_PTR())
#define HEADER_OP(__action)               \
    do                                    \
    {                                     \
        (HEADER_OP_STREAM()) << __action; \
    } while (0);
#define SOURCE_OP_STREAM_PTR() (param.getSourceOpStream())
#define SOURCE_OP_STREAM() (*SOURCE_OP_STREAM_PTR())
#define SOURCE_OP(__action)               \
    do                                    \
    {                                     \
        (SOURCE_OP_STREAM()) << __action; \
    } while (0);
#define BOTH_OP(__action)   \
    do                      \
    {                       \
        HEADER_OP(__action) \
        SOURCE_OP(__action) \
    } while (0);
