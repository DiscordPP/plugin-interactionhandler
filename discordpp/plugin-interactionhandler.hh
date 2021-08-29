#pragma once

namespace discordpp {
template <class BASE>
class PluginInteractionHandler : public BASE, virtual BotStruct {
  public:
    std::multimap<snowflake, handleEvent> interactionHandlers;

    PluginInteractionHandler() {
        handlers.insert(
            {"INTERACTION_CREATE", [this](json msg) {
                 const snowflake id = get_snowflake(msg["data"]["id"]);
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