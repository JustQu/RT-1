# RT-1
Мои файлы парсинга: get_default.c get_first_value.c get_light_type.c  get_obj_mat_type.c  get_tex_cam_type.c  get_tracer_type.c
                    init_parsed_scene.c logs.c  pars_camera.c pars_light.c  pars_material.c pars_obj.c  pars_option.c pars_texture.c
                    parser.c  logs.h  offset.h

Дополнял и изменял файлы: parser.h  scene.h init.c  rt.c

К норме не приведено. Но там должно быть не сложно. Логи не дописал они должны использоваться в функциях валидации в pars_object/light/camera. Там надо будет
переименовать функции add_parsed_object/light/camera... в validate_parsed...

Есть две сцены - 1.txt и cornel_box

Логи пишутся в папку logs. Надо будет решить создавать ее в коде или хранить по дефолту в репозитории.
