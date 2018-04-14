// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Harzcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Wintersonnenwende 2017 (UTC): 2017-12-21T16:28:00+00:00"; // Harzcoin: Wintersonnenwende 2017 (UTC): 2017-12-21T16:28:00+00:00
    const CScript genesisOutputScript = CScript() << ParseHex("04e29491ca745be73af2e0f435bd3e1a53312ca4c9d50f3e2ebec12b9f566fd20d4066d8b4b7f06732062d885aa9fbcf5e32456cf769f13380090f4d324d238e7d") << OP_CHECKSIG; // Harzcoin: 04e29491ca745be73af2e0f435bd3e1a53312ca4c9d50f3e2ebec12b9f566fd20d4066d8b4b7f06732062d885aa9fbcf5e32456cf769f13380090f4d324d238e7d
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000; // Harzcoin: 210000 is a dummy variable here
        consensus.BIP34Height = 1;                  // Harzcoin: 1
        consensus.BIP34Hash = uint256S("0xef1419ca421b282546905eec235dbe5a930545dd9e28574ba52c27386da518f4"); // Harzcoin: 0xef1419ca421b282546905eec235dbe5a930545dd9e28574ba52c27386da518f4
        consensus.BIP65Height = 3; // Harzcoin: 3
        consensus.BIP66Height = 2; // Harzcoin: 2
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Harzcoin: 0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
        consensus.nPowTargetTimespan = 120960; // Harzcoin: (14 * 24 * 60 * 60)/10 = 1/10 of two weeks
        consensus.nPowTargetSpacing = 60; // Harzcoin: one minute
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // Harzcoin: 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // Harzcoin: nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1498713060; // Harzcoin: Thursday, 29. June 2017 05:11:00
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1530249060; // Harzcoin: Friday, 29. June 2018 05:11:00

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1530249060; // Harzcoin: Friday, 29. June 2018 05:11:00
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1561785060; // Harzcoin: Saturday, 29. June 2019 05:11:00

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // Harzcoin: 0x0000000000000000000000000000000000000000000000000000000000000000

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d"); // Harzcoin TODO: Update 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d at height 0

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xd9; // Harzcoin: 0xd9
        pchMessageStart[1] = 0xb4; // Harzcoin: 0xb4
        pchMessageStart[2] = 0xbe; // Harzcoin: 0xbe
        pchMessageStart[3] = 0xfd; // Harzcoin: 0xfd
        nDefaultPort = 1142; // Harzcoin: 1142
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1513873680, 1121874, 0x1e0ffff0, 1, 50 * COIN); // Harzcoin: 1513873680, 1121874, 0x1e0ffff0, 1, 50 * COIN
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d")); // Harzcoin: 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d
        assert(genesis.hashMerkleRoot == uint256S("0x2e998b5755fab943593ba67c4da1e511d41a60b2d7614b551d71a195e8950820")); // Harzcoin: 0x2e998b5755fab943593ba67c4da1e511d41a60b2d7614b551d71a195e8950820

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.emplace_back("dnsseed1.harzcoin.org", true); // Harzcoin: dnsseed1.harzcoin.org
        vSeeds.emplace_back("dnsseed2.harzcoin.org", false);// Harzcoin: dnsseed2.harzcoin.org

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,65); // Harzcoin: 65 (T)
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,100); // Harzcoin: 100
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,193); // Harzcoin: 193
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E}; // Harzcoin: 0x04, 0x88, 0xB2, 0x1E (xpub)
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4}; // Harzcoin: 0x04, 0x88, 0xAD, 0xE4 (xpriv)

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {     0, uint256S("0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d")}, // Harzcoin: 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d (height 0).    // Harzcoin: 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d
            1513873680, // * UNIX timestamp of last known number of transactions                                  // Harzcoin: 1513873680
                     1, // * total number of transactions between genesis and that timestamp                      // Harzcoin: 1
                        //   (the tx=... number in the SetBestChain debug.log lines)
                     1  // * estimated number of transactions per second after that timestamp                     // Harzcoin: 1
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000; // Harzcoin: 210000 is a dummy variable here
        consensus.BIP34Height = 0; // Harzcoin: 0
        consensus.BIP34Hash = uint256S("0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d"); // Harzcoin TODO: Update, for now 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d
        consensus.BIP65Height = 999999; // Harzcoin TODO: Update
        consensus.BIP66Height = 888888; // Harzcoin TODO: Update
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Harzcoin: 0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
        consensus.nPowTargetTimespan = 120960; // Harzcoin: (14 * 24 * 60 * 60)/10 = 1/10 of two weeks
        consensus.nPowTargetSpacing = 60; // Harzcoin: one minute
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // Harzcoin: 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // Harzcoin: nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1498713060; // Harzcoin: Thursday, 29. June 2017 05:11:00
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1530249060; // Harzcoin: Friday, 29. June 2018 05:11:00

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1530249060; // Harzcoin: Friday, 29. June 2018 05:11:00
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1561785060; // Harzcoin: Saturday, 29. June 2019 05:11:00

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // Harzcoin: 0x0000000000000000000000000000000000000000000000000000000000000000

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d"); // Harzcoin TODO: Update, for now 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d

        pchMessageStart[0] = 0x11; // Harzcoin: 0x11
        pchMessageStart[1] = 0x0b; // Harzcoin: 0x0b
        pchMessageStart[2] = 0x09; // Harzcoin: 0x09
        pchMessageStart[3] = 0x04; // Harzcoin: 0x04
        nDefaultPort = 11142; // Harzcoin: 11142
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1513873680, 1121874, 0x1e0ffff0, 1, 50 * COIN); // Harzcoin TODO: Update, for now 1513873680, 1121874, 0x1e0ffff0, 1, 50 * COIN
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d")); // Harzcoin TODO: Update, for now 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d
        assert(genesis.hashMerkleRoot == uint256S("0x2e998b5755fab943593ba67c4da1e511d41a60b2d7614b551d71a195e8950820")); // Harzcoin TODO: Update, for now 0x2e998b5755fab943593ba67c4da1e511d41a60b2d7614b551d71a195e8950820

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("testnet-dnsseed1.harzcoin.org", true); // Harzcoin: testnet-dnsseed1.harzcoin.org
        vSeeds.emplace_back("testnet-dnsseed2.harzcoin.org", false);// Harzcoin: testnet-dnsseed2.harzcoin.org

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111); // Harzcoin: 111 (m or n)
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196); // Harzcoin: 196
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239); // Harzcoin: 239
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // Harzcoin: 0x04, 0x35, 0x87, 0xCF (tpub)
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // Harzcoin: 0x04, 0x35, 0x83, 0x94 (tpriv)

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;


        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d")}, // Harzcoin TODO: Update, for now 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d
            }
        };

        chainTxData = ChainTxData{
            // Harzcoin TODO: Update, for now data as of block 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d (height 0)
            1513873680,
            1,
            1
        };

    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150; // Harzcoin: 150 is a dummy variable here
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // Harzcoin TODO: Update, for now BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // Harzcoin TODO: Update, for now BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Harzcoin: 0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
        consensus.nPowTargetTimespan = 120960; // Harzcoin: (14 * 24 * 60 * 60)/10 = 1/10 of two weeks
        consensus.nPowTargetSpacing = 60; // Harzcoin: one minute
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // Harzcoin: 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Harzcoin: Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // Harzcoin: 0x0000000000000000000000000000000000000000000000000000000000000000

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d"); // Harzcoin TODO: Update, for now 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d at height 0

        pchMessageStart[0] = 0xbf; // Harzcoin: 0xbf
        pchMessageStart[1] = 0xfa; // Harzcoin: 0xfa
        pchMessageStart[2] = 0xb5; // Harzcoin: 0xb5
        pchMessageStart[3] = 0x04; // Harzcoin: 0x04
        nDefaultPort = 21142; // Harzcoin: 21142
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1513873680, 1121874, 0x1e0ffff0, 1, 50 * COIN); // Harzcoin TODO: Update, for now 1513873680, 1121874, 0x1e0ffff0, 1, 50 * COIN
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d")); // Harzcoin TODO: Update, for now 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d
        assert(genesis.hashMerkleRoot == uint256S("0x2e998b5755fab943593ba67c4da1e511d41a60b2d7614b551d71a195e8950820")); // Harzcoin TODO: Update, for now 0x2e998b5755fab943593ba67c4da1e511d41a60b2d7614b551d71a195e8950820

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d")}, // Harzcoin TODO: Update, for now 0x74029d43abd76ab7fca473af3865fb55e8920f8fc1dbab195eab653384e8d58d
            }
        };

        chainTxData = ChainTxData{
            1513873680, // Harzcoin TODO: Update, for now 1513873680
            1, // Harzcoin TODO: Update, for now 1
            1 // Harzcoin TODO: Update, for now 1
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111); // Harzcoin: 111 (m or n)
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196); // Harzcoin: 196
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239); // Harzcoin: 239
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // Harzcoin: 0x04, 0x35, 0x87, 0xCF (tpub)
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // Harzcoin: 0x04, 0x35, 0x83, 0x94 (tpriv)
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
