#pragma once
#include "../../faworld/world.h"
#include <boost/optional.hpp>
#include <cstdint>
#include <vector>

namespace FAWorld
{
    class Player;
    class PlayerInput;
}

namespace Engine
{
    class MultiplayerInterface
    {
    public:
        virtual ~MultiplayerInterface() = default;

        virtual boost::optional<std::vector<FAWorld::PlayerInput>> getAndClearInputs(FAWorld::Tick tick) = 0;
        virtual void update() = 0;
        virtual void verify(FAWorld::Tick tick) = 0;
        virtual bool isServer() const = 0;
        virtual bool isMultiplayer() const = 0;
        virtual void registerNewPlayer(FAWorld::Player* player, uint32_t peerId) = 0;

        static constexpr int32_t RELIABLE_CHANNEL_ID = 0;
        static constexpr int32_t UNRELIABLE_CHANNEL_ID = 0;

        enum class MessageType : uint8_t
        {
            // server-to-client
            MapToClient,
            InputsToClient,

            // client-to-server
            AcknowledgeMapToServer,
            ClientUpdateToServer
        };
    };
}
