serenity_component(
    TestAPP
    REQUIRED
    TARGETS TestAPP
)

set(SOURCES
    main.cpp
)


serenity_app(TestAPP ICON ladyball)
target_link_libraries(TestAPP PRIVATE LibCore LibGfx LibGUI LibMain LibSystem)
