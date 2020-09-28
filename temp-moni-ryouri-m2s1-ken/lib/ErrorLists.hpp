/*
 *  低レイヤーでの初期設定の干渉問題：チェック済み
 */

#pragma once

enum error
{
    none, // success
    auth_failed,
    discrepancy,
    conflict,
    timeout,
    checksum,
    not_ready,
    total,
};