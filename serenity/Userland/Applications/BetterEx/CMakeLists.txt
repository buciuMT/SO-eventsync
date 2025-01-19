serenity_component(
    Better
    REQUIRED
    TARGETS Better
)

compile_gml(window.gml windowGML.cpp)

set(SOURCES
    main.cpp
    widget.cpp
    windowGML.cpp
)



serenity_app(Better ICON ladyball)
target_link_libraries(Better PRIVATE LibCore LibGfx LibGUI LibMain LibSystem)
