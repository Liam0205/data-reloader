gen_rule (
  name = 'all',
  deps = [
    ':reloadable',
    ':reloader_base',
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
