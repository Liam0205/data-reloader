gen_rule (
  name = 'all',
  deps = [
    ':reloadable',
    ':reloader_base',
    ':timer_reloader',
  ]
)

cc_binary(
  name = 'reloadable',
  srcs = [
    'reloadable.cc',
  ],
)

cc_binary(
  name = 'reloader_base',
  srcs = [
    'reloader_base.cc',
  ],
)

cc_binary(
  name = 'timer_reloader',
  srcs = [
    'timer_reloader.cc',
  ],
)
