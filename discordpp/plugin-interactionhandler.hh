#pragma once

namespace discordpp {
template <class BASE>
class PluginInteractionHandler : public BASE, virtual BotStruct {
  public:
    std::multimap<Snowflake, handleEvent> interactionHandlers;

    PluginInteractionHandler() : BASE() {
        handlers.insert(
            {"INTERACTION_CREATE", [this](json msg) {
                 const Snowflake id = msg["data"]["id"].get<Snowflake>();
                 if (interactionHandlers.find(id) ==
                     interactionHandlers.end()) {
                     if (debugUnhandled) {
                         std::cerr << "No interaction handlers defined for "
                                   << id << "\n";
                     }
                 } else {
                     for (auto handler = interactionHandlers.lower_bound(id);
                          handler != interactionHandlers.upper_bound(id);
                          handler++) {
                         handler->second(msg);
                     }
                 }
             }});
    }
};
} // namespace discordpp