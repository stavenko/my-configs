"set nocompatible              " be iMproved, required
"filetype off                  " required

call plug#begin('~/.vim/plugged')

Plug 'nvim-tree/nvim-web-devicons' " optional, for file icons
Plug 'nvim-tree/nvim-tree.lua'
Plug 'rafi/awesome-vim-colorschemes'
Plug 'tpope/vim-fugitive'
Plug 'godlygeek/tabular'
Plug 'preservim/vim-markdown'
Plug 'rust-lang/rust.vim'
Plug 'neoclide/coc.nvim', {'branch': 'release'}
Plug 'airblade/vim-gitgutter'
Plug 'stavenko/ergodox-keymap'
Plug '/usr/local/opt/fzf'
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plug 'junegunn/fzf.vim'
Plug 'honza/vim-snippets'
Plug 'nvim-treesitter/nvim-treesitter', {'do': ':TSUpdate'}
Plug 'nvim-treesitter/nvim-treesitter-textobjects'
Plug 'vimwiki/vimwiki'
Plug 'michal-h21/vim-zettel'

call plug#end()

let g:vimwiki_list = [{'path':'~/projects/notes/','ext':'.md','syntax':'markdown','path_html':'~/projects/notes/html/'}]
let g:zettel_options = [{"disable_front_matter": 1,"front_matter" : [],  "template" :  "~/projects/my-configs/my-zettel-template.tpl"}]
let g:zettel_format = "%d.%m.%y/%H%M%S"
let g:zettel_fzf_command = "rg --column --line-number --ignore-case --no-heading --color=always"


autocmd filetype markdown syn region math start=/\$\$/ end=/\$\$/
autocmd filetype markdown syn match math '\$[^$].\{-}\$'

syntax on
set shiftwidth=2
set tabstop=2
set number

set expandtab
set cindent
"set foldmethod=syntax
"set foldlevelstart=1
set formatoptions=jctql
set backspace=0


" This little command enables <enter> key to complete word using autocomplete
" menu
inoremap <expr> <cr> pumvisible() ? "\<c-y>" : "\<cr>" 
inoremap <expr> <c-н> "\<c-y>"

" Esc works as expected in terminal buffer.
:tnoremap <Esc> <C-\><C-n>

autocmd FileType typescript.tsx setl shiftwidth=2 tabstop=2
autocmd FileType typescript setl shiftwidth=2 tabstop=2
autocmd FileType javascript setl shiftwidth=2 tabstop=2
autocmd FileType cpp setl shiftwidth=2 tabstop=2
autocmd FileType c setl shiftwidth=2 tabstop=2
autocmd FileType rust setl shiftwidth=4 tabstop=4
autocmd FileType markdown setl fo=twan1


au FileType typescript map ˆ :TSDef <CR>
au FileType typescript.tsx map ˆ :TSDef <CR>

set colorcolumn=+1
set textwidth=80


let g:airline#extensions#keymap#enabled = 0
let g:airline#extensions#nerdtree_status = 1

let g:markdown_enable_spell_checking = 0
let g:vim_markdown_folding_disabled = 1

let g:grep_exclude_dirs=['node_modules', '.git']
let g:nvim_typescript#default_mappings=0
let g:nvim_typescript#debug_enabled=1 
let g:nvim_typescript#diagnostics_enable = 1
let g:deoplete#enable_at_startup = 1
let g:syntastic_check_on_open=1
let g:syntastic_always_populate_loc_list = 1
let g:coc_global_extensions=[
 \'coc-lists', 
 \'coc-rust-analyzer', 
 \'coc-clangd', 
 \'coc-json', 
 \'coc-sql',
 \'coc-yaml',
 \'coc-emoji',
 \'coc-marketplace',
 \'coc-spell-checker',
 \'coc-cspell-dicts',
 \'coc-snippets'
 \]
 
set langmap=ЙЦУКЕ;QWERT,ФЫВАП;ASDFG,ЯЧСМИ;ZXCVB,НГШЗХ;YUIOP,РОЛД;HJKL,ТЬ;NM,йцуке;qwert,фывап;asdfg,ячсми;zxcvb,нгшзх;yuiop,ролд;hjkl,ть;nm
" set keymap=russian-ergodox "

imap <C-l> <Plug>(coc-snippets-expand)
imap <Esc><BS> <C-w>
cmap <Esc><BS> <C-w>

" Use <C-j> for select text for visual placeholder of snippet.
vmap <C-j> <Plug>(coc-snippets-select)

" Use <C-j> for jump to next placeholder; it's default of coc.nvim
let g:coc_snippet_next = '<c-j>'

" Use <C-k> for jump to previous placeholder, it's default of coc.nvim
let g:coc_snippet_prev = '<c-k>'


map <leader>n :NvimTreeToggle<CR>
nmap <leader>f :NvimTreeFindFile<CR>
nmap <leader>j :CocList files<CR>
" 
set termguicolors
set background=light
colorscheme flattened_dark
 
set grepprg=""

function! s:get_visual_selection()
  " Why is this not a built-in Vim script function?!
  let [line_start, column_start] = getpos("'<")[1:2]
  let [line_end, column_end] = getpos("'>")[1:2] let lines = getline(line_start, line_end)
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
 
vnoremap * y/<C-r>"<cr> " Copy selection to search buffer
 
nmap <silent> gd <Plug>(coc-definition)
nmap <silent> gy <Plug>(coc-type-definition)
nmap <silent> gi <Plug>(coc-implementation)
nmap <silent> gr <Plug>(coc-references)
" 
" 
"set keymap=russian-ergodox
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

"nmap <silent> <leader>x :%FormatXML<CR>
"vmap <silent> <leader>x :FormatXML<CR>

"command! -range=% PrettifyTypescript execute '!yarn prettier --write %'
autocmd FileType typescript nmap <silent><leader>a :CocCommand prettier.formatFile<CR>
autocmd FileType typescript.tsx nmap <silent><leader>a :CocCommand prettier.formatFile<CR>
autocmd FileType rust nmap <silent><leader>a :call CocAction('format')<CR>
autocmd BufNewFile,BufRead *.scenario   set syntax=yaml

" location list hot keys
nmap <silent> <leader>q :CocList diagnostics<CR>
nmap <silent> <leader>m :CocCommand rust-analyzer.parentModule<CR>
nmap <silent> <leader>rm :CocCommand rust-analyzer.parentModule<CR>
nmap <silent> <leader>rc :CocCommand rust-analyzer.expandMacro<CR>
nmap <silent> <leader>rr :CocCommand rust-analyzer.reloadWorkspace<CR>

vmap <leader>z <Plug>(coc-codeaction-selected)
nmap <leader>z <Plug>(coc-codeaction-selected) 
nmap <silent> <leader>vv :Git<cr>
nmap <silent> <leader>vp :Git push<cr>
nmap <silent> <leader>vfp :Git push --force<cr>

nmap <leader>xn :ZettelNew<cr>
nmap <leader>xo :ZettelOpen<cr>
nmap <leader>xs :ZettelSearch<cr>

map <leader>gt :tag <c-r><c-w><cr>
nnoremap <F2> :w!<CR>
nnoremap <F10> :q!<CR>

lua << EOF

local nvim_tree = require "nvim-tree"
local function my_on_attach(bufnr)
  local api = require "nvim-tree.api"
  local function opts(desc)
    return { desc = "nvim-tree: " .. desc, buffer = bufnr, noremap = true, silent = true, nowait = true }
  end

  -- default mappings
  api.config.mappings.default_on_attach(bufnr)

  -- custom mappings
  vim.keymap.set('n', 'cd', api.tree.change_root_to_node,        opts('CD'))

end
nvim_tree.setup {
  sync_root_with_cwd = true,
  on_attach = my_on_attach,
}
vim.lsp.set_log_level 'debug'

require'nvim-treesitter.configs'.setup {
  textobjects = {
    select = {
      enable = true,

      -- Automatically jump forward to textobj, similar to targets.vim
      lookahead = true,

      keymaps = {
        -- You can use the capture groups defined in textobjects.scm
        ["aa"] = "@parameter.outer",
        ["ia"] = "@parameter.inner",
        -- ["ac"] = "@class.outer",
        -- You can optionally set descriptions to the mappings (used in the desc parameter of
        -- nvim_buf_set_keymap) which plugins like which-key display
        -- ["ic"] = { query = "@class.inner", desc = "Select inner part of a class region" },
        -- You can also use captures from other query groups like `locals.scm`
        -- ["as"] = { query = "@scope", query_group = "locals", desc = "Select language scope" },
      },
      -- You can choose the select mode (default is charwise 'v')
      --
      -- Can also be a function which gets passed a table with the keys
      -- * query_string: eg '@function.inner'
      -- * method: eg 'v' or 'o'
      -- and should return the mode ('v', 'V', or '<c-v>') or a table
      -- mapping query_strings to modes.
      selection_modes = {
        ['@parameter.outer'] = 'v', -- charwise
        -- ['@function.outer'] = 'V', -- linewise
        -- ['@class.outer'] = '<c-v>', -- blockwise
      },
      -- If you set this to `true` (default is `false`) then any textobject is
      -- extended to include preceding or succeeding whitespace. Succeeding
      -- whitespace has priority in order to act similarly to eg the built-in
      -- `ap`.
      --
      -- Can also be a function which gets passed a table with the keys
      -- * query_string: eg '@function.inner'
      -- * selection_mode: eg 'v'
      -- and should return true of false
      include_surrounding_whitespace = true,
    },
  },
}
EOF
