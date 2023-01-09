"set nocompatible              " be iMproved, required
"filetype off                  " required

call plug#begin('~/.vim/plugged')

Plug 'nvim-tree/nvim-web-devicons' " optional, for file icons
Plug 'nvim-tree/nvim-tree.lua'

Plug 'rafi/awesome-vim-colorschemes'
Plug 'tpope/vim-fugitive'
Plug 'gabrielelana/vim-markdown'
Plug 'rust-lang/rust.vim'
Plug 'neoclide/coc.nvim', {'branch': 'release'}
Plug 'airblade/vim-gitgutter'
Plug 'stavenko/ergodox-keymap'
Plug '/usr/local/opt/fzf'
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plug 'junegunn/fzf.vim'
call plug#end()

"filetype plugin indent on    " required
"filetype plugin on

lua << EOF
  local nvim_tree = require "nvim-tree"
  nvim_tree.setup {
    sync_root_with_cwd = true,
    view = {
      adaptive_size = true,
      mappings = {
        list = {
          {key ="cd", action="cd"}
        }
      }
    }
  }
  vim.lsp.set_log_level 'debug'
EOF


syntax on
set shiftwidth=2
set tabstop=2
set number

set expandtab
set cindent
set foldmethod=syntax
set foldlevelstart=1
set formatoptions=jctql


" This little command enables <enter> key to complete word using autocomplete
" menu
inoremap <expr> <cr> pumvisible() ? "\<c-y>" : "\<cr>" 

autocmd FileType typescript.tsx setl shiftwidth=2 tabstop=2
autocmd FileType typescript setl shiftwidth=2 tabstop=2
autocmd FileType javascript setl shiftwidth=2 tabstop=2
autocmd FileType cpp setl shiftwidth=2 tabstop=2
autocmd FileType c setl shiftwidth=2 tabstop=2
autocmd FileType rust setl shiftwidth=4 tabstop=4


au FileType typescript map ˆ :TSDef <CR>
au FileType typescript.tsx map ˆ :TSDef <CR>

set colorcolumn=+1
set textwidth=80


let g:airline#extensions#keymap#enabled = 0
let g:airline#extensions#nerdtree_status = 1

let g:markdown_enable_spell_checking = 0

let g:grep_exclude_dirs=['node_modules', '.git']
let g:nvim_typescript#default_mappings=0
let g:nvim_typescript#debug_enabled=1
let g:nvim_typescript#diagnostics_enable = 1
let g:deoplete#enable_at_startup = 1
let g:syntastic_check_on_open=1
let g:syntastic_always_populate_loc_list = 1
let g:rustfmt_command = "rustup run nightly rustfmt"
"let g:rustfmt_options = "--edition=2021"
 
 
map <leader>n :NvimTreeToggle<CR>
nmap <leader>f :NvimTreeFindFile<CR>
nmap <leader>j :GFiles<CR>
" 
set termguicolors
set background=light
colorscheme PaperColor
 
set grepprg=""

function! s:get_visual_selection()
  " Why is this not a built-in Vim script function?!
  let [line_start, column_start] = getpos("'<")[1:2]
  let [line_end, column_end] = getpos("'>")[1:2]
  let lines = getline(line_start, line_end)
  if len(lines) == 0
    return ''
  endif
  let lines[-1] = lines[-1][: column_end - (&selection == 'inclusive' ? 1 : 2)]
  let lines[0] = lines[0][column_start - 1:]
  return join(lines, "\n")
endfunction

function! GrepBufferCommandSearch() 
  let l:pattern = shellescape(@/)
  let l:filename = expand('%')
  let l:command = "grep -n " . l:filename . " -e "  . l:pattern 
  let grepOutput = systemlist(l:command) 
  if len(grepOutput) > 0
    call setqflist([])
    let l:list = []
    for line in grepOutput
      let data = split(line, ':')
      if  len(data) >= 2
        let l:text = join(data[1: len(data)-1], ':')
        call add(l:list, {'filename': l:filename, 'lnum': data[0], 'text': l:text})
      endif

    endfor
    call setloclist(winnr(),l:list)
    exec "rightbelow lopen"
  endif
endfunction

function! GrepBufferCommandSelection() 
  let l:pattern = s:get_visual_selection()
  let l:filename = expand('%')
  let l:command = "grep -n " . l:filename . " -e " . l:pattern 
  let grepOutput = systemlist(l:command) 
  if len(grepOutput) > 0
    call setqflist([])
    let l:list = []
    for line in grepOutput
      let data = split(line, ':')
      if  len(data) >= 2
        let l:text = join(data[1: len(data)-1], ':')
        call add(l:list, {'filename': l:filename, 'lnum': data[0], 'text': l:text})
      endif

    endfor
    call setloclist(winnr(),l:list)
    exec "leftabove lopen"
  endif
endfunction

function! GrepCommand(pattern, gparams) 
  let l:exclude_dirs=[]
  for item in g:grep_exclude_dirs
    call add(l:exclude_dirs, '--exclude-dir ' . item )
  endfor
  let l:pattern = substitute(a:pattern, '\\>', '\\b', "g")
  let l:pattern = substitute(l:pattern, '\\<', '\\b', "g")
  let l:command = "rg " . a:gparams . " . -e " . shellescape(l:pattern)
  let grepOutput = systemlist(l:command) 
  call setqflist([])
  if len(grepOutput) > 0
    let l:list = []
    for line in grepOutput
      let data = split(line, ':')
      if  len(data) >= 3
        let l:text = join(data[2: len(data)-1], ':')
        call add(l:list, {'filename': data[0], 'lnum': data[1], 'text': l:text})
      endif

    endfor
    call setqflist(l:list)
    exec "botright copen"
  endif
endfunction

command! -nargs=1 VGrep :call GrepCommand(<f-args>, '-n --color never --no-heading')
command! -nargs=1 VGrepi :call GrepCommand(<f-args>, '-rni')
command! -range VGREPFV :call GrepBufferCommandSelection()

vmap <silent> <leader>8 :VGREPFV<cr>
nmap <silent> <leader>8 :call GrepBufferCommandSearch()<cr>
 
vnoremap * y/<C-r>"<cr>
 
nmap <silent> gd <Plug>(coc-definition)
nmap <silent> gy <Plug>(coc-type-definition)
nmap <silent> gi <Plug>(coc-implementation)
nmap <silent> gr <Plug>(coc-references)
" 
" 
set keymap=russian-ergodox
set iminsert=0
set imsearch=0

" XML formatter
function! DoFormatXML() range
  " Save the file type
  let l:origft = &ft

  " Clean the file type
  set ft=

  " Add fake initial tag (so we can process multiple top-level elements)
  exe ":let l:beforeFirstLine=" . a:firstline . "-1"
  if l:beforeFirstLine < 0
    let l:beforeFirstLine=0
  endif
  exe a:lastline . "put ='</PrettyXML>'"
  exe l:beforeFirstLine . "put ='<PrettyXML>'"
  exe ":let l:newLastLine=" . a:lastline . "+2"
  if l:newLastLine > line('$')
    let l:newLastLine=line('$')
  endif

  " Remove XML header
  exe ":" . a:firstline . "," . a:lastline . "s/<\?xml\\_.*\?>\\_s*//e"

  " Recalculate last line of the edited code
  let l:newLastLine=search('</PrettyXML>')

  " Execute external formatter
  exe ":silent " . a:firstline . "," . l:newLastLine . "!xmllint --noblanks --format --recover -"

  " Recalculate first and last lines of the edited code
  let l:newFirstLine=search('<PrettyXML>')
  let l:newLastLine=search('</PrettyXML>')

  " Get inner range
  let l:innerFirstLine=l:newFirstLine+1
  let l:innerLastLine=l:newLastLine-1

  " Remove extra unnecessary indentation
  exe ":silent " . l:innerFirstLine . "," . l:innerLastLine "s/^  //e"

  " Remove fake tag
  exe l:newLastLine . "d"
  exe l:newFirstLine . "d"

  " Put the cursor at the first line of the edited code
  exe ":" . l:newFirstLine

  " Restore the file type
  exe "set ft=" . l:origft
endfunction
command! -range=% FormatXML <line1>,<line2>call DoFormatXML()

nmap <silent> <leader>x :%FormatXML<CR>
vmap <silent> <leader>x :FormatXML<CR>

"command! -range=% PrettifyTypescript execute '!yarn prettier --write %'
autocmd FileType typescript nmap <silent><leader>a :CocCommand prettier.formatFile<CR>
autocmd FileType typescript.tsx nmap <silent><leader>a :CocCommand prettier.formatFile<CR>
autocmd FileType rust nmap <silent><leader>a :RustFmt<CR>

" location list hot keys
nmap <silent> <leader>q :CocList diagnostics<CR>

vmap <leader>z <Plug>(coc-codeaction-selected)
nmap <leader>z <Plug>(coc-codeaction-selected) 
